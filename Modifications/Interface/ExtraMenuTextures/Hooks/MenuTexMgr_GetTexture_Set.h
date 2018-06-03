#pragma once

#include "Villain\Hook.h"

class MenuTexMgr_GetTexture_Set : public Hook
{
	void PatchCode(HANDLE process);
	void InstallDetour();
};

extern const DWORD MenuTexMgr_GetTexture_Set_Pointer;
extern const int MenuTexMgr_GetTexture_Set_Length;
extern void(__stdcall* MenuTexMgr_GetTexture_Set_Detour)();
extern void MenuTexMgr_GetTexture_Set_Method();