#include "MenuTexMgr_GetTexture_SetReturn.h"

#include "Villain\Generic.h"

#include "..\ExtraMenuTextures.h"

void MenuTexMgr_GetTexture_SetReturn::PatchCode(HANDLE process)
{
	FillProcessMemory(process, MenuTexMgr_GetTexture_SetReturn_Pointer, MenuTexMgr_GetTexture_SetReturn_Length);
}

void MenuTexMgr_GetTexture_SetReturn::InstallDetour()
{
	MenuTexMgr_GetTexture_SetReturn_Detour = (void(__stdcall*)())(DWORD*)MenuTexMgr_GetTexture_SetReturn_Pointer;
	LONG attached = DetourAttach(&(PVOID&)MenuTexMgr_GetTexture_SetReturn_Detour, &MenuTexMgr_GetTexture_SetReturn_Method);

	if (attached != NO_ERROR)
	{
		MessageBox(nullptr, "MenuTexMgr_GetTexture_SetReturn", "Fiesta", MB_ICONERROR);
	}
}

extern const DWORD MenuTexMgr_GetTexture_SetReturn_Pointer = 0x0042A50A;
extern const int MenuTexMgr_GetTexture_SetReturn_Length = 7;

void(__stdcall* MenuTexMgr_GetTexture_SetReturn_Detour)();
void __declspec(naked) MenuTexMgr_GetTexture_SetReturn_Method()
{
	__asm
	{
		CMP EBX, 0x20
		JB _OnBelowLimit
		
		PRE_NON_NAKED_CALL

		PUSH EBX
		CALL GetLoadedTexturePointer
		ADD ESP, 4
		
		POST_NON_NAKED_CALL
		MOV_RESULT_TO(EAX)

		JMP MenuTexMgr_GetTexture_SetReturn_Detour

		_OnBelowLimit :
			MOV EAX, DWORD PTR DS : [EBX * 4 + 0xA89CA0]
			JMP MenuTexMgr_GetTexture_SetReturn_Detour
	}
}