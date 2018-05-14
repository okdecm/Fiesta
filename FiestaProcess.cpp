#include <windows.h>

#include <ThirdParty\Detours\Detours.h>

#include "FiestaProcess.h"

#include "Fiesta.h"

#include "Game\Pointers.h"
#include "Hooks\CustomClasses\CustomClasses.h"

void FiestaProcess::OnPatchCode(HANDLE process)
{
	if (Fiesta::Settings->GetCustomClassesEnabled())
	{
		//FillMemory(&(PVOID&)Hook_CharCreateClassWin_CreateWin_Pointer, Hook_CharCreateClassWin_CreateWin_Length, 0x90);

		BYTE Hook_CharCreateClassWin_CreateWin_Buffer[Hook_CharCreateClassWin_CreateWin_Length] = { 0x90 }; // NOP
		memset(Hook_CharCreateClassWin_CreateWin_Buffer, 0x90, sizeof(Hook_CharCreateClassWin_CreateWin_Buffer));

		WriteProcessMemory(process, (LPVOID)Hook_CharCreateClassWin_CreateWin_Pointer, Hook_CharCreateClassWin_CreateWin_Buffer, sizeof(Hook_CharCreateClassWin_CreateWin_Buffer), NULL);
	}
}

void FiestaProcess::OnInstallDetours()
{
	if (Fiesta::Settings->GetCustomClassesEnabled())
	{
		Hook_CharCreateClassWin_CreateWin = (void(__stdcall*)())(DWORD*)Hook_CharCreateClassWin_CreateWin_Pointer;
		DetourAttach(&(PVOID&)Hook_CharCreateClassWin_CreateWin, CharCreateClassWin_CreateWin);
	}
}