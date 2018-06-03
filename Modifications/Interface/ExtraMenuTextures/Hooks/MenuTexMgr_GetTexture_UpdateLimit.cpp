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
	LONG attached = DetourAttach(&(PVOID&)MenuTexMgr_GetTexture_UpdateLimit_Detour, &MenuTexMgr_GetTexture_UpdateLimit_Method);

	if (attached != NO_ERROR)
	{
		MessageBox(nullptr, "MenuTexMgr_GetTexture_UpdateLimit", "Fiesta", MB_ICONERROR);
	}
}

extern const DWORD MenuTexMgr_GetTexture_UpdateLimit_Pointer = 0x0042A4A7;
extern const int MenuTexMgr_GetTexture_UpdateLimit_Length = 18;

void(__stdcall* MenuTexMgr_GetTexture_UpdateLimit_Detour)();
void __declspec(naked) MenuTexMgr_GetTexture_UpdateLimit_Method()
{
	__asm
	{
		//MOV EBX, 0x21
		CMP EBX, 0x20
		JB _OnBelowLimit
		PUSHAD
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
			PUSH 0
			PUSH EDI
			LEA EDI, DWORD PTR DS : [ESP + 4]
			PUSHAD
			PUSH EBX
			CALL GetLoadedTexturePointer
			ADD ESP, 4
			MOV DWORD PTR DS : [EDI], EAX
			POPAD
			POP EDI
			ADD ESP, 4
			CMP DWORD PTR DS : [ESP - 4], 0
			JMP MenuTexMgr_GetTexture_UpdateLimit_Detour

		_OnBelowLimit:
			CMP DWORD PTR DS : [EBX * 4 + 0xA89CA0], 0
			JMP MenuTexMgr_GetTexture_UpdateLimit_Detour
	}
}