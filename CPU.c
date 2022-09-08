#include <stdio.h>
#include <intrin.h>
#include <string.h>
#include <objbase.h>
#include <systemInfo.h>
#include <TCHAR.h>
#include <pdh.h>
void getCPUName(char* name) {
	int cpuInfo[4] = {
		-1
	};

	memset(name, 0, sizeof(name));

	__cpuid(cpuInfo, 0x80000002);
	memcpy(name, cpuInfo, sizeof(cpuInfo));

	__cpuid(cpuInfo, 0x80000003);
	memcpy(name + 16, cpuInfo, sizeof(cpuInfo));

	__cpuid(cpuInfo, 0x80000004);
	memcpy(name + 32, cpuInfo, sizeof(cpuInfo));
}

static PDH_HQUERY cpuQuery;
static PDH_HCOUNTER cpuTotal;

void CPUUsageInit() {
	PdhOpenQuery(NULL, (DWORD_PTR)NULL, &cpuQuery);
	// You can also use L"\\Processor(*)\\% Processor Time" and get individual CPU values with PdhGetFormattedCounterArray()
	PdhAddEnglishCounter(cpuQuery, L"\\Processor(_Total)\\% Processor Time", (DWORD_PTR)NULL, &cpuTotal);
	PdhCollectQueryData(cpuQuery);
}

void updateCPUUsage() {
	PDH_FMT_COUNTERVALUE counterVal;

	PdhCollectQueryData(cpuQuery);
	PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
	systemInfo.CPU.utilization = (float)counterVal.doubleValue;
}