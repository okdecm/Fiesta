#pragma once

#include <vector>

#include "CustomClass.h"

class CustomClasses
{
	private:
		static void InitializeButtonData();
	public:
		static vector<CustomClass> Classes;

		static void Initialize();
};

struct CustomClassButtonData
{
	unsigned int ClassID;
	char* ButtonName;
	unsigned int ButtonIndex;
};

extern int CustomClassesCount;
extern CustomClassButtonData* CustomClassButtonDatas;

extern void(__stdcall* Hook_CharCreateClassWin_CreateWin)();
extern void CharCreateClassWin_CreateWin();

extern void CharCreateClassWin_CreateWin_AddButton(char* buttonName, int buttonIndex, int classID);