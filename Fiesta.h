#pragma once

#include "FiestaSettings.h"
#include "FiestaProcess.h"

#include "Modifications\Interface\ExtraMenuTextures\ExtraMenuTextures.h"

class Fiesta
{
	public:
		static FiestaSettings* Settings;
		static FiestaProcess* Process;

		static DWORD WINAPI Install(LPVOID lpParameter);
};

extern ExtraMenuTextures* extraMenuTextures;