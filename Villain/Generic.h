#pragma once

char* CreateBuffer(int size);
char* CreateBuffer(int size, BYTE with);
bool FileExists(char* path);
void FillProcessMemory(HANDLE process, DWORD pointer, int length, BYTE with);
void FillProcessMemory(HANDLE process, DWORD pointer, int length);
void InstallDetour(DWORD pointer, PVOID callback, PVOID Hook);