#include "MenuTexMgr_GetTexture_Set.h"

#include "Villain\Generic.h"

#include "..\ExtraMenuTextures.h"

void MenuTexMgr_GetTexture_Set::PatchCode(HANDLE process)
{
	FillProcessMemory(process, MenuTexMgr_GetTexture_Set_Pointer, MenuTexMgr_GetTexture_Set_Length);
}

void MenuTexMgr_GetTexture_Set::InstallDetour()
{
	MenuTexMgr_GetTexture_Set_Detour = (void(__stdcall*)())(DWORD*)MenuTexMgr_GetTexture_Set_Pointer;
	LONG attached = DetourAttach(&(PVOID&)MenuTexMgr_GetTexture_Set_Detour, &MenuTexMgr_GetTexture_Set_Method);

	if (attached != NO_ERROR)
	{
		MessageBox(nullptr, "MenuTexMgr_GetTexture_Set", "Fiesta", MB_ICONERROR);
	}
}

extern const DWORD MenuTexMgr_GetTexture_Set_Pointer = 0x0042A4F3;
extern const int MenuTexMgr_GetTexture_Set_Length = 7;

void(__stdcall* MenuTexMgr_GetTexture_Set_Detour)();
void __declspec(naked) MenuTexMgr_GetTexture_Set_Method()
{
	DWORD textureLoadedAt;

	__asm
	{
		CMP EBX, 0x20
		JB _OnBelowLimit
		PUSHAD
		PUSH EDI
		PUSH EBX
		CALL SetLoadedTexturePointer
		ADD ESP, 8
		POPAD
		JMP MenuTexMgr_GetTexture_Set_Detour

		_OnBelowLimit:
			MOV DWORD PTR DS : [EBX * 4 + 0xA89CA0], EDI
			JMP MenuTexMgr_GetTexture_Set_Detour
	}
}