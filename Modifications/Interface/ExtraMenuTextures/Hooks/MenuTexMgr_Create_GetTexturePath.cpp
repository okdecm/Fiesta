#include "MenuTexMgr_Create_GetTexturePath.h"

#include "Villain\Generic.h"

#include "..\ExtraMenuTextures.h"

void MenuTexMgr_Create_GetTexturePath::PatchCode(HANDLE process)
{
	FillProcessMemory(process, MenuTexMgr_Create_GetTexturePath_Pointer, MenuTexMgr_Create_GetTexturePath_Length);
}

void MenuTexMgr_Create_GetTexturePath::InstallDetour()
{
	MenuTexMgr_Create_GetTexturePath_Detour = (void(__stdcall*)())(DWORD*)MenuTexMgr_Create_GetTexturePath_Pointer;
	DetourAttach(&(PVOID&)MenuTexMgr_Create_GetTexturePath_Detour, &MenuTexMgr_Create_GetTexturePath_Method);
}

extern const DWORD MenuTexMgr_Create_GetTexturePath_Pointer = 0x0042A415;
extern const int MenuTexMgr_Create_GetTexturePath_Length = 7;

void(__stdcall* MenuTexMgr_Create_GetTexturePath_Detour)();
void __declspec(naked) MenuTexMgr_Create_GetTexturePath_Method()
{
	__asm
	{
		CMP ESI, 0x20
		JB _OnBelowLimit
		PUSH ESI
		CALL GetTexturePath
		JMP MenuTexMgr_Create_GetTexturePath_Detour

		_OnBelowLimit:
		MOV EAX, DWORD PTR DS : [ESI * 4 + 0xA6A0B0]
		JMP MenuTexMgr_Create_GetTexturePath_Detour
	}
}