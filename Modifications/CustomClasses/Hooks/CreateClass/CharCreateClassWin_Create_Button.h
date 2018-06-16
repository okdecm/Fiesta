#pragma once

#include "Villain\Hook.h"

class CharCreateClassWin_Create_Button : public Hook
{
	void PatchCode(HANDLE process);
	void InstallDetour();
};

extern const DWORD CharCreateClassWin_Create_Button_Pointer;
extern const int CharCreateClassWin_Create_Button_Length;
extern void(__stdcall* CharCreateClassWin_Create_Button_Detour)();
extern void CharCreateClassWin_Create_Button_Method();