#include <conio.h>
#include <stdio.h>
#include <state.h>
#include <stdbool.h>
state_t state;
void updateState() {
	int key = 0;
	if (_kbhit()) {
		key = _getch();
	}
	//printf("key: %d", key);
	if (key == 'q' || key == 68) {
		printf("Exiting!");
		state.exiting = true;
	}
}