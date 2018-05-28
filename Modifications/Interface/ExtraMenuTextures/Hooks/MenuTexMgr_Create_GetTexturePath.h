#pragma once

#include "Villain\Hook.h"

class MenuTexMgr_Create_GetTexturePath : public Hook
{
	void PatchCode(HANDLE process);
	void InstallDetour();
};

extern const DWORD MenuTexMgr_Create_GetTexturePath_Pointer;
extern const int MenuTexMgr_Create_GetTexturePath_Length;
extern void(__stdcall* MenuTexMgr_Create_GetTexturePath_Detour)();
extern void MenuTexMgr_Create_GetTexturePath_Method();