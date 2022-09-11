#include <stdio.h>
#include <systemInfo.h>
#include <RAM.h>
#include <CPU.h>
#include <cursor.h>
#include <stdbool.h>
#include <Windows.h>
#include <Psapi.h>
#include <colors.h>
#include <process.h>
#include <terminal.h>
#include <keyboard.h>
#include <state.h>
extern DWORD WINAPI secondThreadFunc(LPVOID param);
extern DWORD WINAPI thirdThreadFunc(LPVOID param);
typedef struct MyData {
	int val1;
	int val2;
} MYDATA, *PMYDATA;
PMYDATA pDataArray[2];
DWORD threadIDs[2];
extern void redrawScreen();
char* bottomBarBuffer;
int main() {
	setCursorState(false);
	state.threads.thread1readyfor3rdthread = false;
	state.threads.thread2readyfor3rdthread = false;
	state.selectedLine = 1;
	initSysInfo();
	getTerminalWidthAndHeight();
	CPUUsageInit();
	bottomBarBuffer = malloc(sizeof(char) * 310);

	redrawScreen();
	CreateThread(NULL, 0, secondThreadFunc, NULL, 0, &threadIDs[0]);
	CreateThread(NULL, 0, thirdThreadFunc, NULL, 0, &threadIDs[1]);
	// TODO: Add bar using "|" character
	uint16_t prevTermWidth  = systemInfo.terminal.width;
	uint16_t prevTermHeight = systemInfo.terminal.height;
	uint16_t i = 0;
	while (true) {
		state.threads.thread1readyfor2ndthread = false;
		state.threads.thread1readyfor3rdthread = false;
		if (prevTermWidth != systemInfo.terminal.width || prevTermHeight != systemInfo.terminal.height) {
			moveCursor(0, 0);
			printf("\033[1;1H\033[2J"); // Clear screen
			prevTermWidth = systemInfo.terminal.width;
			prevTermHeight = systemInfo.terminal.height;
			redrawScreen();
		}
		i++;
		if (i == 25000) {
			i = 0;
			//redrawScreen();
		}
		getTerminalWidthAndHeight();
		updateState();
		if (state.exiting) {
			break;
		}
		state.threads.thread1readyfor3rdthread = true;
		state.threads.thread1readyfor2ndthread = true;
	}
	// TODO: Fix this, this really should be freed.
	// free(systemInfo.CPU.name);
	free(bottomBarBuffer);
	return 0;
}