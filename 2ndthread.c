#include <stdio.h>
#include <colors.h>
#include <cursor.h>
#include <systemInfo.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>
#include <process.h>
#include <RAM.h>


extern time_t start;
time_t end;
DWORD WINAPI secondThreadFunc(LPVOID param) {
	(void)param;
	while (true) {
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
		
		updateSysInfo();

		// TODO: Detect window size change and perform a full redraw to prevent goofiness
		/// STUFF FOR CPU ///
		uint8_t percentLen = 1;
		if (systemInfo.CPU.utilization > 9.99f) {
			percentLen = 2;
		}
		if (systemInfo.CPU.utilization > 99.99f) {
			percentLen = 3;
		}

		moveCursor(51 - (2 + percentLen), 1);
		printf("%s  %.1f%%%s", BRIGHT_BLACK_FG, systemInfo.CPU.utilization, RESET);


		RAMDrawUsageBar();

		moveCursor(0, 6);
		printProcesses();

		Sleep(750 - (DWORD)((DWORD)end - (DWORD)start));
	}
}