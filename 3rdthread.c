#include <Windows.h>
#include <stdbool.h>
#include <process.h>
#include <cursor.h>
#include <state.h>
#include <stdio.h>
DWORD WINAPI thirdThreadFunc(LPVOID param) {
	(void)param;
	while (true) {
		state.threads.thread3readyfor2ndthread = true;
		while (true) {
			if (state.threads.thread1readyfor3rdthread && state.threads.thread2readyfor3rdthread) {
				state.threads.thread3readyfor2ndthread = false;
				break;
			}
		}
		moveCursor(0, 6);
		printProcesses();
		Sleep(10);
	}
	return 0;
}