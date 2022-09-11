#include <colors.h>
#include <stdint.h>
#include <systemInfo.h>
#include <stdio.h>
#include <string.h>
#include <cursor.h>
extern char* bottomBarBuffer;
void drawMainTopBar() {
	moveCursor(1, 4);

	printf(
		"  \x1b[30;42m Main %s \x1b[30;44m I/O %s\r\n"
		"%s    PID^\x1b[30;42mUSER      PRI  NI  VIRT   RES   SHR S  CPU%% MEM%%   TIME+  Command",
		RESET, RESET, CYAN_BG_BLACK_FG
	);
	printf("\x1b[30;42m");
	for (size_t i = strlen("    PID^USER      PRI  NI  VIRT   RES   SHR S  CPU% MEM%   TIME+  Command"); i < systemInfo.terminal.width; i++) {
		putchar(' ');
	}
	printf("%s", RESET);
}
void redrawScreen() {
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
	moveCursor(1, systemInfo.terminal.height);
	memset(bottomBarBuffer, '\0', sizeof(char) * 310);
	snprintf(bottomBarBuffer, sizeof(char) * 310, "%s%sF1%sHelp  %s%sF2%sSetup %s%sF3%sSearch%s%sF4%sFilter%s%sF5%sTree  %s%sF6%sSortBy%s%sF7%sNice -%s%sF8%sNice +%s%sF9%sKill  %s%sF10%sQuit%s",
		RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, RESET, BRIGHT_WHITE_FG, CYAN_BG_BLACK_FG, CYAN_BG_BLACK_FG);
	printf(bottomBarBuffer);
	for (size_t i = strlen("F1Help  F2Setup F3SearchF4FilterF5Tree  F6SortByF7Nice -F8Nice +F9Kill  F10Quit"); i < systemInfo.terminal.width; i++) {
		putchar(' ');
	}
	printf("%s", RESET);

	drawMainTopBar();
}