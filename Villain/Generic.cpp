#include <windows.h>
#include <fstream>
#include "Generic.h"

char* CreateBuffer(int size)
{
	return CreateBuffer(size, 0x0);
}

char* CreateBuffer(int size, BYTE with)
{
	char* buffer = new char[size];

	FillMemory(buffer, size, with);

	return buffer;
}

bool FileExists(char* path)
{
	return (bool)std::ifstream(path);
}

void FillProcessMemory(HANDLE process, DWORD pointer, int length, BYTE with)
{
	WriteProcessMemory(process, (LPVOID)pointer, CreateBuffer(length, with), length, NULL);
}

void FillProcessMemory(HANDLE process, DWORD pointer, int length)
{
	FillProcessMemory(process, pointer, length, 0x90);
}

void InstallDetour(DWORD pointer, PVOID callback, PVOID hook)
{
	//Hook = (void(__stdcall*)())(DWORD*)Hook_CharCreateClassWin_CreateWin_Pointer;
	//DetourAttach(&(PVOID&)Hook_CharCreateClassWin_CreateWin, hook);
}