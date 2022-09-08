#include <stdint.h>
#include <stdio.h>
void moveCursor(uint16_t x, uint16_t y) {
	printf("\033[%d;%dH", y, x);
}