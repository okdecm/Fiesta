#pragma once

BYTE* CreateBuffer(int size);
BYTE* CreateBuffer(int size, BYTE with);
char* CreateString(int size);
bool FileExists(char* path);
void FillProcessMemory(HANDLE process, DWORD pointer, int length, BYTE with);
void FillProcessMemory(HANDLE process, DWORD pointer, int length);
void InstallDetour(DWORD pointer, PVOID callback, PVOID Hook);