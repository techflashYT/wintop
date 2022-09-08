#pragma once
#include <stdint.h>
typedef struct {
	/// <summary>
	/// Struct for information about the CPU
	/// </summary>
	struct {
		/// <summary>
		/// The number of CPU cores
		/// </summary>
		uint16_t cores;
		/// <summary>
		/// The name of the CPU gathered by the `cpuid` instruction
		/// </summary>
		char *name;
		float utilization;
	} CPU;
	/// <summary>
	/// Struct for information about the RAM
	/// </summary>
	struct {
		/// <summary>
		/// The size of the unit.
		/// 0: KB
		/// 1: MB
		/// 2: GB
		/// 3: TB
		/// </summary>
		uint8_t identifier;
		/// <summary>
		/// Size of the RAM in the system in *identifier*.
		/// </summary>
		uint64_t size;
		float utilization;
	} RAM;

	struct {
		/// <summary>
		/// The current width that the terminal has
		/// </summary>
		uint16_t width;
		/// <summary>
		/// The current height that the terminal has
		/// </summary>
		uint16_t height;
	} terminal;

} systemInfo_t;
extern systemInfo_t systemInfo;
void initSysInfo();
void updateSysInfo();