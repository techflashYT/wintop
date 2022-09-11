#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
void moveCursor(uint16_t x, uint16_t y) {
	printf("\033[%d;%dH", y, x);
}
void setCursorState(bool enabled) {
	if (enabled) {
		printf("\033[0m\033[?25h");
		return;
	}
	else {
		printf("\033[0m\033[?25l");
	}
}