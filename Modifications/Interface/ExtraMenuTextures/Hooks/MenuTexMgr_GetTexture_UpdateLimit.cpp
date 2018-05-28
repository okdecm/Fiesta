#include "MenuTexMgr_GetTexture_UpdateLimit.h"

#include "Villain\Generic.h"

#include "..\ExtraMenuTextures.h"

void MenuTexMgr_GetTexture_UpdateLimit::PatchCode(HANDLE process)
{
	FillProcessMemory(process, MenuTexMgr_GetTexture_UpdateLimit_Pointer, MenuTexMgr_GetTexture_UpdateLimit_Length);
}

void MenuTexMgr_GetTexture_UpdateLimit::InstallDetour()
{
	MenuTexMgr_GetTexture_UpdateLimit_Detour = (void(__stdcall*)())(DWORD*)MenuTexMgr_GetTexture_UpdateLimit_Pointer;
	DetourAttach(&(PVOID&)MenuTexMgr_GetTexture_UpdateLimit_Detour, &MenuTexMgr_GetTexture_UpdateLimit_Method);
}

extern const DWORD MenuTexMgr_GetTexture_UpdateLimit_Pointer = 0x0042A4A7;
extern const int MenuTexMgr_GetTexture_UpdateLimit_Length = 18;

void(__stdcall* MenuTexMgr_GetTexture_UpdateLimit_Detour)();
void __declspec(naked) MenuTexMgr_GetTexture_UpdateLimit_Method()
{
	__asm
	{

		MOV EBX, 0x21
		PUSHAD
		CMP EBX, 0x20
		JB _OnBelowLimit
		PUSH EBX
		CALL ExtraTextureExists
		ADD ESP, 4
		TEST EAX, EAX
		JNZ _OnExtraTexture
		POPAD
		XOR EAX, EAX
		POP EBX
		POP EBP
		RETN

		_OnExtraTexture:
		POPAD
		JMP MenuTexMgr_GetTexture_UpdateLimit_Detour

		_OnBelowLimit:
		POPAD
		CMP DWORD PTR DS : [EBX * 4 + 0xA89CA0], 0
		JMP MenuTexMgr_GetTexture_UpdateLimit_Detour
	}
}