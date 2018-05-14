#pragma once

#include <windows.h>

// Hooks
const DWORD Hook_CharCreateClassWin_CreateWin_Pointer = 0x00405158;
const DWORD Hook_CharCreateClassWin_CreateWin_Length = 5;

// Game
const DWORD NiTMapBase_LuaScriptType_SetAt_Pointer = 0x0064E830;
const DWORD UIUtil_CreateButton_Pointer = 0x00443DD0;
const DWORD KERNEL32_InterlockedIncrement_Pointer = 0x0096D2A0;

const DWORD CharCreateClassWin_OnSetClass_Pointer = 0x00404C90;