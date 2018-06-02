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
	LONG attached = DetourAttach(&(PVOID&)MenuTexMgr_Create_GetTexturePath_Detour, &MenuTexMgr_Create_GetTexturePath_Method);

	if (attached != NO_ERROR)
	{
		MessageBox(nullptr, "MenuTexMgr_Create_GetTexturePath", "Fiesta", MB_ICONERROR);
	}
}

extern const DWORD MenuTexMgr_Create_GetTexturePath_Pointer = 0x0042A415;
extern const int MenuTexMgr_Create_GetTexturePath_Length = 7;

void(__stdcall* MenuTexMgr_Create_GetTexturePath_Detour)();
void __declspec(naked) MenuTexMgr_Create_GetTexturePath_Method()
{
	DWORD texturePath;

	__asm
	{
		CMP ESI, 0x20
		JB _OnBelowLimit
		PUSHAD
		PUSH ESI
		CALL GetTexturePath
		ADD ESP, 4
		MOV texturePath, EAX
		POPAD
		MOV EAX, texturePath
		JMP MenuTexMgr_Create_GetTexturePath_Detour

		_OnBelowLimit:
		MOV EAX, DWORD PTR DS : [ESI * 4 + 0xA6A0B0]
		JMP MenuTexMgr_Create_GetTexturePath_Detour
	}
}