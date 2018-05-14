#pragma once

#include "FiestaSettings.h"
#include "FiestaProcess.h"

class Fiesta
{
	public:
		static FiestaSettings* Settings;
		static FiestaProcess* Process;

		static DWORD WINAPI InstallHook(LPVOID lpParameter);
};