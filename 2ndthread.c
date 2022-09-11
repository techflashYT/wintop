#include <stdio.h>
#include <colors.h>
#include <cursor.h>
#include <systemInfo.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>
#include <RAM.h>
#include <state.h>
#include <time.h>

time_t start;
time_t end;
extern void drawMainTopBar();
DWORD WINAPI secondThreadFunc(LPVOID param) {
	(void)param;
	while (true) {
		state.threads.thread2readyfor3rdthread = true;
		while (true) {
			if (state.threads.thread1readyfor2ndthread && state.threads.thread3readyfor2ndthread) {
				break;
			}
		}
		start = clock();
		state.threads.thread2readyfor3rdthread = false;
		drawMainTopBar();
		
		state.threads.thread2readyfor3rdthread = true;
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

		state.threads.thread2readyfor3rdthread = false;
		moveCursor(51 - (2 + percentLen), 1);
		printf("%s  %.1f%%%s", BRIGHT_BLACK_FG, systemInfo.CPU.utilization, RESET);

		end = clock();

		RAMDrawUsageBar();
		state.threads.thread2readyfor3rdthread = true;
		DWORD len = 1500 - (DWORD)((DWORD)end - (DWORD)start);
		Sleep(len);
	}
	return 0;
}