#include "MenuTexMgr_GetTexture_Check.h"

#include "Villain\Generic.h"

#include "..\ExtraMenuTextures.h"

void MenuTexMgr_GetTexture_Check::PatchCode(HANDLE process)
{
	FillProcessMemory(process, MenuTexMgr_GetTexture_Check_Pointer, MenuTexMgr_GetTexture_Check_Length);
}

void MenuTexMgr_GetTexture_Check::InstallDetour()
{
	MenuTexMgr_GetTexture_Check_Detour = (void(__stdcall*)())(DWORD*)MenuTexMgr_GetTexture_Check_Pointer;
	LONG attached = DetourAttach(&(PVOID&)MenuTexMgr_GetTexture_Check_Detour, &MenuTexMgr_GetTexture_Check_Method);

	if (attached != NO_ERROR)
	{
		MessageBox(nullptr, "MenuTexMgr_GetTexture_Check", "Fiesta", MB_ICONERROR);
	}
}

extern const DWORD MenuTexMgr_GetTexture_Check_Pointer = 0x0042A4C3;
extern const int MenuTexMgr_GetTexture_Check_Length = 7;

void(__stdcall* MenuTexMgr_GetTexture_Check_Detour)();
void __declspec(naked) MenuTexMgr_GetTexture_Check_Method()
{
	DWORD textureLoadedAt;

	__asm
	{
		CMP EBX, 0x20
		JB _OnBelowLimit
		PUSHAD
		PUSH EBX
		CALL GetLoadedTexturePointer
		ADD ESP, 4
		MOV textureLoadedAt, EAX
		POPAD
		MOV ESI, textureLoadedAt
		JMP MenuTexMgr_GetTexture_Check_Detour

		_OnBelowLimit :
			MOV ESI, DWORD PTR DS : [EBX * 4 + 0xA89CA0]
			JMP MenuTexMgr_GetTexture_Check_Detour
	}
}