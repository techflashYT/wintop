#pragma once
#include <stdint.h>
typedef struct {
	/// <summary>
	/// Identifier for the size of the uint.
	/// 0: Kilobytes
	/// 1: Megabytes
	/// 2: Gigabytes
	/// 3: Terabytes
	/// </summary>
	uint8_t identifier;
	uint64_t size;
} RAMInfo_t;
RAMInfo_t RAMBytesToKB_MB_GB(uint64_t bytes);
const char* RAMIdentifierToString(uint8_t identifier);
void updateRAMUsage();
const char* RAMUtilToKB_MB_GBStr(float util);
void RAMDrawUsageBar();