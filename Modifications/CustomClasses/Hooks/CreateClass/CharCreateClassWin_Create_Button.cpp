#include "CharCreateClassWin_Create_Button.h"

#include "Villain\Generic.h"

#include "Game\Pointers.h"

void CharCreateClassWin_Create_Button::PatchCode(HANDLE process)
{
	FillProcessMemory(process, CharCreateClassWin_Create_Button_Pointer, CharCreateClassWin_Create_Button_Length);
}

void CharCreateClassWin_Create_Button::InstallDetour()
{
	CharCreateClassWin_Create_Button_Detour = (void(__stdcall*)())(DWORD*)CharCreateClassWin_Create_Button_Pointer;
	LONG attached = DetourAttach(&(PVOID&)CharCreateClassWin_Create_Button_Detour, &CharCreateClassWin_Create_Button_Method);

	if (attached != NO_ERROR)
	{
		MessageBox(nullptr, "CharCreateClassWin_Create_Button", "Fiesta", MB_ICONERROR);
	}
}

extern const DWORD CharCreateClassWin_Create_Button_Pointer = 0x00405158;
extern const int CharCreateClassWin_Create_Button_Length = 5;

void(__stdcall* CharCreateClassWin_Create_Button_Detour)();
void __declspec(naked) CharCreateClassWin_Create_Button_Method()
{
	__asm PUSHAD

	for (int i )
	{
		__asm
		{
			CALL NiTMapBase_LuaScriptType_SetAt_Pointer
			PUSH 3
			PUSH 0

			PUSH 6
			LEA ECX, DWORD PTR SS : [EBP - 2C]
			CALL UIUtil_CreateButton_Pointer
			PUSH ECX
			MOV ECX, ESP
			MOV DWORD PTR SS : [EBP + 8], ESP
			MOV DWORD PTR DS : [ECX], EAX
			TEST EAX, EAX
			JE _OnFinish
			ADD EAX, 4
			PUSH EAX
			CALL DWORD PTR DS : [KERNEL32_InterlockedIncrement_Pointer]

			_OnFinish:
				PUSH 1C
				LEA ECX, DWORD PTR DS : [ESI + 178]
				CALL 0x0064E830
		}
	}

	__asm POPAD
}