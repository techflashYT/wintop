#include <Windows.h>
#include <stdbool.h>
#include <process.h>
#include <cursor.h>
#include <state.h>
DWORD WINAPI thirdThreadFunc(LPVOID param) {
	(void)param;
	while (true) {
		while (true) {
			if (state.threads.thread1readyfor3rdthread && state.threads.thread2readyfor3rdthread) {
				break;
			}
		}
		moveCursor(0, 6);
		printProcesses();
		Sleep(10);
		
	}
	return 0;
}