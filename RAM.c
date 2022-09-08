#include <stdint.h>
#include <stdio.h>
#include <RAM.h>
#include <systemInfo.h>
#include <Windows.h>
#include <colors.h>
#include <cursor.h>
RAMInfo_t RAMBytesToKB_MB_GB(uint64_t bytes) {
	// Working backwards
	uint64_t tb = 1099511627776;
	uint64_t gb = 1073741824;
	uint32_t mb = 1048576;
	uint16_t kb = 1024;
	RAMInfo_t retval = {
		.identifier = 0,
		.size = 0
	};
	if (bytes >= tb) {
		retval.identifier = 2;
		retval.size = bytes / gb;
		return retval;
	}
	if (bytes >= gb) {
		retval.identifier = 1;
		retval.size = bytes / mb;
		return retval;
	}
	if (bytes >= mb) {
		retval.identifier = 0;
		retval.size = bytes / kb;
		return retval;
	}
	// NOTE: This is basically a panic case, if this triggers, we KNOW we have wrong info,
	// as I don't think any versions of windows will run on less than 1MB of RAM
	if (bytes >= kb) {
		retval.identifier = 0xFF;
		retval.size = bytes;
		return retval;
	}
	return retval;
}
const char identifiers[4][3] = {
	"KB",
	"MB",
	"GB",
	"TB"
};
const char* RAMIdentifierToString(uint8_t identifier) {
	return identifiers[identifier];
}

void updateRAMUsage() {
	MEMORYSTATUSEX memstat = {
		.dwLength = sizeof(MEMORYSTATUSEX)
	};
	GlobalMemoryStatusEx(&memstat);
	systemInfo.RAM.utilization = (float)memstat.dwMemoryLoad;
}
char buffer[10];
const char* RAMUtilToKB_MB_GBStr(float util) {
	float used = (float)((float)systemInfo.RAM.size * (float)((float)util / 100.0f));
	if (used > 999.999999999999f) {
		snprintf(buffer, sizeof(buffer), "%.1f%s", (float)(used /1024.0f), RAMIdentifierToString(systemInfo.RAM.identifier + 1));
	}
	else {
		snprintf(buffer, sizeof(buffer), "%.1f%s", used, RAMIdentifierToString(systemInfo.RAM.identifier));
	}
	return buffer;
}

void RAMDrawUsageBar() {
	uint8_t percentLen = 1;
	float size = ((float)systemInfo.RAM.size / 1024); // Should give something along the lines of 15.8 GB or smth
	if (systemInfo.RAM.utilization > 9) {
		percentLen = 2;
	}
	if (systemInfo.RAM.utilization > 99) {
		percentLen = 3;
	}
	moveCursor(51 - (2 + percentLen + (size > 9 ? 3 : 4) + 2 + 2 + 1), 2);
	char barBuffer[25];
	memset(barBuffer, '\0', sizeof(char) * 25);
	/*size -= 6;*/
	const char* util = RAMUtilToKB_MB_GBStr(systemInfo.RAM.utilization);
	snprintf(barBuffer, sizeof(char) * 25, "%s%s/%.1f%s%s", BRIGHT_BLACK_FG, util, size, RAMIdentifierToString(systemInfo.RAM.identifier + 1), RESET);
	uint8_t i = 0;
	char test[] = "\x1b[1;30m0.0KB/0.0KB\x1b[0m";

	// TODO: This is INTENSE duct tape, fix this!!
	int64_t len = strlen(barBuffer) - strlen(test);
	if (size > 9.999999999999999999999999999999999999999999f) {
		if (strlen(util) == 6) { // 2 digit number
			for (i = 0; i <= len - 1; i++) {
				putchar(' ');
			}
		}
		else {
			for (i = 0; i <= len + 1; i++) {
				putchar(' ');
			}
		}
	}
	else { // 2 digit number
		for (i = 0; i <= len + 3; i++) {
			putchar(' ');
		}
	}
	puts(barBuffer);
}