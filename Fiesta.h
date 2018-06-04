#pragma once

#include "FiestaSettings.h"
#include "FiestaProcess.h"

#include "Modifications\Interface\ExtraMenuTextures\ExtraMenuTextures.h"
#include "Modifications\CustomClasses\CustomClasses.h"

class Fiesta
{
	public:
		static FiestaSettings* Settings;
		static FiestaProcess* Process;

		static DWORD WINAPI Install(LPVOID lpParameter);
};

extern ExtraMenuTextures* extraMenuTextures;
extern CustomClasses* customClasses;