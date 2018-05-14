#include <windows.h>
#include <iostream>

#include "Fiesta.h"

#include "Hooks\CustomClasses\CustomClasses.h"

FiestaSettings* Fiesta::Settings = new FiestaSettings();
FiestaProcess* Fiesta::Process = new FiestaProcess();

DWORD WINAPI Fiesta::InstallHook(LPVOID lpParameter)
{
	Process->Initialize();

	Settings->SetDllInstance(static_cast<HMODULE>(lpParameter));

	char iniPath[MAX_PATH] = { 0 };
	sprintf_s(iniPath, "%sFiesta.ini", Process->GetDirectory());

	int loadSettingsError = Settings->LoadSettings(iniPath);

	switch (loadSettingsError)
	{
		case LoadSettings_File_Not_Found:
			MessageBox(nullptr, "Could not find the file \"Fiesta.ini\"", "Fiesta", MB_ICONERROR);

			// TODO: Leigh said to pause the process before we do anything- ASK HIM HOW
			//Process->ResumeAllThreads();
			return 0;
		break;
	}

	int patchError = Process->PatchCode();

	if (patchError > 0)
	{
		char patchErrorMessage[256];
		sprintf_s(patchErrorMessage, 256, "There was an error patching Fiesta.");

		MessageBox(NULL, patchErrorMessage, "Fiesta", MB_ICONERROR);

		return 0;
	}

	bool hookError = Process->InstallDetours();

	if (hookError)
	{
		char hookErrorMessage[256];
		sprintf_s(hookErrorMessage, 256, "There was an error modifying Fiesta.");

		MessageBox(NULL, hookErrorMessage, "Fiesta", MB_ICONERROR);

		return 0;
	}

	if (Settings->GetCustomClassesEnabled())
	{
		CustomClasses::Initialize();
	}

	return 0;
}