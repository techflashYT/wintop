#include <systemInfo.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <CPU.h>
#include <RAM.h>
#include <colors.h>
#include <version.h>
#include <terminal.h>
systemInfo_t systemInfo;
void updateSysInfo() {
	updateCPUUsage();
	updateRAMUsage();
	getTerminalWidthAndHeight();
}
void initSysInfo() {
	SYSTEM_INFO __sysinfo;
	GetSystemInfo(&__sysinfo);

	systemInfo.CPU.cores = (uint16_t)__sysinfo.dwNumberOfProcessors;
	systemInfo.CPU.name = malloc(sizeof(char) * 40);
	
	MEMORYSTATUSEX __memstatus = { 0 };
	__memstatus.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&__memstatus);
	RAMInfo_t __raminfo = RAMBytesToKB_MB_GB(__memstatus.ullTotalPhys);
	if (__raminfo.identifier == 0) {
		fprintf(stderr,
			"%s[ERROR]%s RAM size detected as less than 1MB.  This is most likely in error.%s\r\n"
			"Please report this problem to the wintop GitHub page (https://github.com/techflashYT/wintop)\r\n"
			"Please attach the following information:\r\n"
			"  - wintop version: %d.%d.%d\r\n"
			"  - Detected RAM ammount: %llu%s\r\n"
			"  - Detected RAM ammount (raw): %llu\r\n",
			BRIGHT_RED_FG, CYAN_FG, RESET, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, __raminfo.size, RAMIdentifierToString(__raminfo.identifier), __memstatus.ullTotalPhys
		);
		abort();
	}
	systemInfo.RAM.size = __raminfo.size;
	systemInfo.RAM.identifier = __raminfo.identifier;
	for (uint8_t i = 0; i < 40; i++) {
		systemInfo.CPU.name[i] = '\0';
	}
	
	getCPUName(systemInfo.CPU.name);

	systemInfo.CPU.utilization = 0;
	systemInfo.RAM.utilization = 0;
}