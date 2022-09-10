#include <conio.h>
#include <stdio.h>
#include <state.h>
#include <stdbool.h>
#include <cursor.h>
#include <Windows.h>
state_t state;
void checkKeys(int key) {
	// down arrow
	if (key == 80) {
		state.selectedLine++;
	}
	// up arrow
	else if (key == 72) {
		if (state.selectedLine != 1) {
			state.selectedLine--;
		}
	}
	// 'F10'
	else if (key == 68) {
		printf("Exiting!");
		state.exiting = true;
	}
	// 'q'
	else if (key == 113) {
		printf("Exiting!");
		state.exiting = true;
	}
}
void updateState() {
	int key = 0;
	if (_kbhit()) {
		key = _getch();
	}
	checkKeys(key);
	//moveCursor(0, 23);
	//printf("key: %d\r\n\r\n", key);
	// TODO: Code hangs here at getch, fix.
	//if (key == 0 || key == 0xE0) {
	//	key = _getch();
	//	checkKeys(key);
	//}

}