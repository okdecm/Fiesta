#pragma once

#include "Villain\Hook.h"

class MenuTexMgr_GetTexture_SetReturn : public Hook
{
	void PatchCode(HANDLE process);
	void InstallDetour();
};

extern const DWORD MenuTexMgr_GetTexture_SetReturn_Pointer;
extern const int MenuTexMgr_GetTexture_SetReturn_Length;
extern void(__stdcall* MenuTexMgr_GetTexture_SetReturn_Detour)();
extern void MenuTexMgr_GetTexture_SetReturn_Method();