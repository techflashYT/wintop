#include <stdint.h>
#include <stdbool.h>
typedef struct {
	uint16_t selectedLine;
	bool exiting;
} state_t;
extern state_t state;
void updateState();