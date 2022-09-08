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
void printProcess(DWORD processID, uint16_t line) {
	if (line <= state.selectedLine) {
		printf("\x1b[30m\x1b[46m");
	}
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

	for (uint8_t i = 0; i <= (6 - len); i++) {
		putchar(' ');
	}
	printf("%d                                                           ", processID);
	printf("%ls\r\n", processName);
	

	if (line != state.selectedLine) {
		printf("\x1b[0m");
	}
    // Release the handle to the process.
	
    CloseHandle(processHandle);
}
void printProcesses() {
	DWORD processes[1024], needed, numOfProcesses;

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
	for (uint16_t i = 0; i < 10; i++) {
		if (processes[i] != 0) {
			printProcess(processes[i], i);
		}
	}
}