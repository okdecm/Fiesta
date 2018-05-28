#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <ThirdParty\Detours\Detours.h>

#include "Process.h"

#include "Generic.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

void Process::Initialize()
{
	char* path = new char[MAX_PATH];

	GetModuleFileNameA((HINSTANCE)&__ImageBase, path, MAX_PATH);

	char* drive = new char[3];
	char* directory = new char[MAX_PATH];

	_splitpath(path, drive, directory, NULL, NULL);

	_directory = new char[MAX_PATH];

	sprintf(_directory, "%s%s", drive, directory);
}

int Process::PatchCode()
{
	DWORD imageBase = (DWORD)GetModuleHandle(0);

	PIMAGE_SECTION_HEADER codeSection;

	if (!GetSectionHeaderInfo(".text", codeSection))
	{
		return PatchCode_Header_Not_Found;
	}

	DWORD baseCodeAddress = imageBase + codeSection->VirtualAddress;

	DWORD processId = GetProcessId(GetCurrentProcess());

	HANDLE process = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, 0, processId);

	if (!process)
	{
		return PatchCode_Could_Not_Open_Process;
	}

	DWORD lpflOldProtect = 0;

	VirtualProtectEx(process, (DWORD*)baseCodeAddress, codeSection->SizeOfRawData, PAGE_EXECUTE_READWRITE, &lpflOldProtect);

	__raise OnPatchCode(process);

	CloseHandle(process);

	return PatchCode_Success;
}

bool Process::InstallDetours()
{
	bool result = false;

	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	__raise OnInstallDetours();

	result |= (DetourTransactionCommit() != 0);

	return result;
}

bool Process::GetSectionHeaderInfo(char* sectionName, PIMAGE_SECTION_HEADER& dest)
{
	const DWORD dwBaseAddress = (DWORD)GetModuleHandle(0);

	PIMAGE_DOS_HEADER dosHeader;
	PIMAGE_NT_HEADERS ntHeader;

	dosHeader = (PIMAGE_DOS_HEADER)dwBaseAddress;
	ntHeader = (PIMAGE_NT_HEADERS)((DWORD)(dosHeader)+(dosHeader->e_lfanew));

	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(ntHeader);

	int sectionCount = 0;
	while (sectionCount <= ntHeader->FileHeader.NumberOfSections)
	{
		if (strstr(sectionName, (char*)section->Name))
		{
			dest = section;

			return true;
		}

		section = IMAGE_FIRST_SECTION(ntHeader) + sectionCount;
		sectionCount++;
	}

	return false;
}

void Process::ResumeAllThreads()
{
	THREADENTRY32 ThreadEntry;
	DWORD dwProcessID = GetCurrentProcessId();

	ThreadEntry.dwSize = sizeof(THREADENTRY32);
	HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwProcessID);

	if (Thread32First(hThreadSnapshot, &ThreadEntry))
	{
		do
		{
			if (ThreadEntry.th32OwnerProcessID == dwProcessID)
			{
				HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, true, ThreadEntry.th32ThreadID);

				if (hThread == nullptr) continue;

				if (WaitForSingleObject(hThread, 0) > WAIT_OBJECT_0)
				{
					ResumeThread(hThread);
				}

				CloseHandle(hThread);
			}

		} while (Thread32Next(hThreadSnapshot, &ThreadEntry));

		CloseHandle(hThreadSnapshot);
	}

	// Fixes problems with SetWindowsHookEx and probably other things.
	Sleep(1000);
}