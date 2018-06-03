#include <windows.h>
#include <iostream>

#include "CustomClasses.h"

#include "Fiesta.h"

#include "Game\Pointers.h"

vector<CustomClass> CustomClasses::Classes;

int CustomClassesCount;
CustomClassButtonData* CustomClassButtonDatas;

void CustomClasses::Initialize()
{
	char jsonPath[MAX_PATH] = { 0 };
	sprintf_s(jsonPath, "%sCustomClasses.json", Fiesta::Process->GetDirectory());

	Classes = CustomClass::DeserializeFromJSONFile(jsonPath);

	CustomClassesCount = Classes.size();

	CustomClasses::InitializeButtonData();
}

void CustomClasses::InitializeButtonData()
{
	int classesCount = CustomClasses::Classes.size();

	CustomClassButtonDatas = new CustomClassButtonData[classesCount];

	int baseButtonIndex = 6;

	for (int i = 0; i < classesCount; i++)
	{
		CustomClass customClass = CustomClasses::Classes[i];

		//int classID = customClass.ID;
		//int buttonIndex = (baseButtonIndex + i);
		//char buttonName[32] = { 0 };
		//sprintf_s(buttonName, "Class_%s", customClass.Name.c_str());

		CustomClassButtonDatas[i].ClassID = 0x1c;
		CustomClassButtonDatas[i].ButtonName = "Class_Pirate";
		CustomClassButtonDatas[i].ButtonIndex = 6;

		// Testing - remove
		break;
	}
}

void(__stdcall* Hook_CharCreateClassWin_CreateWin)();
void __declspec(naked) CharCreateClassWin_CreateWin()
{
	__asm
	{
		call NiTMapBase_LuaScriptType_SetAt_Pointer
		PUSHAD

		MOV ECX, CustomClassesCount
		CMP ECX, 0
		JZ _noCustomClasses

		_addNextClass :
		PUSH ECX

			PUSH 3
			PUSH 0
			MOV ECX, DWORD PTR DS : [CustomClassButtonDatas]
			PUSH DWORD PTR DS : [ECX + 4] // buttonName
			PUSH DWORD PTR DS : [ECX + 8] // buttonIndex
			LEA ECX, DWORD PTR SS : [EBP - 0x2C]
			CALL UIUtil_CreateButton_Pointer
			PUSH ECX
			MOV ECX, ESP
			MOV DWORD PTR SS : [EBP + 0x8], ESP
			MOV DWORD PTR DS : [ECX], EAX
			TEST EAX, EAX
			JE SHORT _skipInterlockedIncrement
			ADD EAX, 0x4
			PUSH EAX
			CALL DWORD PTR DS : [KERNEL32_InterlockedIncrement_Pointer]
			_skipInterlockedIncrement :
			MOV ECX, DWORD PTR DS : [CustomClassButtonDatas]
			PUSH DWORD PTR DS : [ECX] // classID
			LEA ECX, DWORD PTR DS : [ESI + 0x178]
			call NiTMapBase_LuaScriptType_SetAt_Pointer

			POP ECX

			DEC ECX
			CMP ECX, 0
			JA _addNextClass

			_noCustomClasses :
		POPAD
			JMP Hook_CharCreateClassWin_CreateWin
	}
}