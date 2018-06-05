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

extern const DWORD MenuTexMgr_Create_GetTexturePath_Pointer = 0x004086E9;
extern const int MenuTexMgr_Create_GetTexturePath_Length = 7;

void(__stdcall* MenuTexMgr_Create_GetTexturePath_Detour)();
void __declspec(naked) MenuTexMgr_Create_GetTexturePath_Method()
{
	__asm
	{
		CMP EAX, 0x26
		JB _OnBelowLimit
		PUSH 0
		PUSH EDI
		LEA EDI, DWORD PTR DS : [ESP + 4]
		PUSHAD
		PUSH EAX
		CALL GetTexturePath
		ADD ESP, 4
		MOV DWORD PTR DS : [EDI], EAX
		POPAD
		POP EDI
		MOV ECX, DWORD PTR DS : [ESP]
		ADD ESP, 4
		JMP MenuTexMgr_Create_GetTexturePath_Detour

		_OnBelowLimit:
			MOV ECX, DWORD PTR DS : [EAX * 4 + 0x904018]
			JMP MenuTexMgr_Create_GetTexturePath_Detour
	}
}