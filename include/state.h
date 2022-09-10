#include <stdint.h>
#include <stdbool.h>
typedef struct {
	uint16_t selectedLine;
	bool exiting;
	struct {
		bool thread1readyfor3rdthread;
		bool thread2readyfor3rdthread;
	} threads;
} state_t;
extern state_t state;
void updateState();