#include <stdio.h>
#include <systemInfo.h>
#include <RAM.h>
#include <CPU.h>
#include <cursor.h>
#include <stdbool.h>
#include <Windows.h>
#include <Psapi.h>
#include <colors.h>
#include <time.h>
#include <process.h>
#include <terminal.h>
#include <conio.h>
#include <keyboard.h>
int main() {
	initSysInfo();
	getTerminalWidthAndHeight();
	CPUUsageInit();
	keysArr = malloc(sizeof(char) * 125);
	printf("\033[1;1H\033[2J"); // Clear screen
	
	printf("  %sCPU%s[", CYAN_FG, BRIGHT_WHITE_FG);
	for (uint8_t i = 0; i <= 46; i++) {
		putchar(' ');
	}
	printf("%s]%s\r\n", BRIGHT_WHITE_FG, RESET);
	printf("  %sMem%s[", CYAN_FG, BRIGHT_WHITE_FG);
	for (uint8_t i = 0; i <= 46; i++) {
		putchar(' ');
	}
	printf("%s]%s\r\n", BRIGHT_WHITE_FG, RESET);
	moveCursor(1, 4);
	char* buffer = malloc(sizeof(char) * 250);

	printf (
		"  \x1b[30;42m Main %s \x1b[30;44m I/O %s\r\n"
		"%s    PID^\x1b[30;42mUSER      PRI  NI  VIRT   RES   SHR S  CPU%% MEM%%   TIME+  Command",
		RESET, RESET, CYAN_BG_BLACK_FG
	);
	printf("\x1b[30;42m");
	for (size_t i = strlen("    PID^USER      PRI  NI  VIRT   RES   SHR S  CPU% MEM%   TIME+  Command"); i < systemInfo.terminal.width; i++) {
		putchar(' ');
	}
	moveCursor(1, systemInfo.terminal.height - 1);
	char* bottomBarBuffer = malloc(sizeof(char) * 310);
	memset(bottomBarBuffer, '\0', sizeof(char) * 310);
	snprintf(bottomBarBuffer, sizeof(char) * 310, "%s%sF1%sHelp  %s%sF2%sSetup %s%sF3%sSearch%s%sF4%sFilter%s%sF5%sTree  %s%sF6%sSortBy%s%sF7%sNice -%s%sF8%sNice +%s%sF9%sKill  %s%sF10%sQuit%s",
		RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, CYAN_BG_BLACK_FG);
	printf(bottomBarBuffer);
	for (size_t i = strlen("F1Help  F2Setup F3SearchF4FilterF5Tree  F6SortByF7Nice -F8Nice +F9Kill  F10Quit"); i < systemInfo.terminal.width; i++) {
		putchar(' ');
	}
	printf("%s", RESET);
	time_t start;
	time_t end;
	// TODO: Add bar using "|" character
	int key = 0;
	while (true) {
		start = clock();
		updateSysInfo();
		/// STUFF FOR CPU ///
		uint8_t percentLen = 1;
		if (systemInfo.CPU.utilization > 9) {
			percentLen = 2;
		}
		if (systemInfo.CPU.utilization > 99) {
			percentLen = 3;
		}

		moveCursor(51 - (2 + percentLen), 1);
		printf("%s  %.1f%%%s", BRIGHT_BLACK_FG, systemInfo.CPU.utilization, RESET);
		

		RAMDrawUsageBar();
		
		moveCursor(0, 6);
		printProcesses();
		if (_kbhit()) {
			key = _getch();
		}
		//printf("key: %d", key);
		if (key == 'q' || key == 68) {
			printf("Exiting!");
			break;
		}
		end = clock();
		Sleep(750 - (DWORD)((DWORD)end - (DWORD)start));
	}
	// TODO: Fix this, this really should be freed.
	// free(systemInfo.CPU.name);
	free(buffer);
	free(keysArr);
	return 0;
}