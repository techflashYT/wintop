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
#include <keyboard.h>
#include <state.h>
time_t start;
DWORD WINAPI secondThreadFunc(LPVOID param);
typedef struct MyData {
	int val1;
	int val2;
} MYDATA, *PMYDATA;
PMYDATA pDataArray[1];
DWORD threadID;
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
	CreateThread(NULL, 0, secondThreadFunc, NULL, 0, &threadID);
	// TODO: Add bar using "|" character
	while (true) {
		start = clock();
		updateState();
		if (state.exiting) {
			break;
		}
	}
	// TODO: Fix this, this really should be freed.
	// free(systemInfo.CPU.name);
	free(bottomBarBuffer);
	free(keysArr);
	return 0;
}