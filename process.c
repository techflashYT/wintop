#pragma once
#include <stdint.h>
#include <tchar.h>
#include <version.h>
#include <Windows.h>
#include <colors.h>
#include <stdio.h>
#include <Psapi.h>
#include <cursor.h>
#include <state.h>
#include <systemInfo.h>
#include <stdbool.h>
void printProcess(DWORD processID, uint16_t line) {
	printf("\x1b[0m");
	if (line == state.selectedLine) {
		printf("\x1b[30m\x1b[46m");
	}
	moveCursor(1, 5 + line);
    TCHAR processName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    // Get the process name.

    if (NULL != processHandle) {
        HMODULE moduleHandle;
        DWORD needed;

        if (EnumProcessModules(processHandle, &moduleHandle, sizeof(moduleHandle), &needed)) {
            GetModuleBaseName(processHandle, moduleHandle, processName, sizeof(processName) / sizeof(TCHAR));
        }
    }

    // Print the process name and identifier.
	uint8_t len = 1;
	if (processID > 9) {
		len = 2;
	}
	if (processID > 99) {
		len = 3;
	}
	if (processID > 999) {
		len = 4;
	}
	if (processID > 9999) {
		len = 5;
	}
	if (processID > 99999) {
		len = 6;
	}

	for (uint8_t i2 = 0; i2 <= (6 - len); i2++) {
		putchar(' ');
	}
	printf("%d                                                           ", processID);
	printf("%ls", processName);

	for (size_t i2 = 66 + wcslen(processName); i2 < systemInfo.terminal.width; i2++) {
		putchar(' ');
	}
	printf("\r\n");
	if (line == state.selectedLine) {
		printf("\x1b[0m");
	}
    // Release the handle to the process.
	
    CloseHandle(processHandle);
}
DWORD processes[1024], needed, numOfProcesses;
uint8_t i = 9;
void printProcesses() {
	i++;
	bool threadState[4] = { false, false, false, false };
	threadState[0] = state.threads.thread1readyfor2ndthread;
	threadState[1] = state.threads.thread1readyfor3rdthread;
	threadState[2] = state.threads.thread2readyfor3rdthread;
	threadState[3] = state.threads.thread3readyfor2ndthread;
	state.threads.thread1readyfor2ndthread = false;
	state.threads.thread1readyfor3rdthread = false;
	state.threads.thread2readyfor3rdthread = false;
	state.threads.thread3readyfor2ndthread = false;
	//moveCursor(1, 6);
	if (i == 10) {
		i = 0;
		if (!EnumProcesses(processes, sizeof(processes), &needed)) {
			fprintf(stderr,
				"%s[ERROR]%s Unable to enumerate processes!%s\r\n"
				"Please report this problem to the wintop GitHub page (https://github.com/techflashYT/wintop)\r\n"
				"Please attach the following information:\r\n"
				"  - wintop version: %d.%d.%d\r\n",
				BRIGHT_RED_FG, CYAN_FG, RESET, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH
			);
			abort();
		}
		numOfProcesses = needed / sizeof(DWORD);
	}
	moveCursor(1, 6);
	for (uint16_t i2 = 0; i2 < 10; i2++) {
		if (processes[i2] != 0) {
			printProcess(processes[i2], i2);
		}
	}
	state.threads.thread1readyfor2ndthread = threadState[0];
	state.threads.thread1readyfor3rdthread = threadState[1];
	state.threads.thread2readyfor3rdthread = threadState[2];
	state.threads.thread3readyfor2ndthread = threadState[3];
}