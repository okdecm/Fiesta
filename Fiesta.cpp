#include <windows.h>
#include <iostream>

#include "Fiesta.h"

#include "Modifications\Interface\ExtraMenuTextures\ExtraMenuTextures.h"

FiestaSettings* Fiesta::Settings = new FiestaSettings();
FiestaProcess* Fiesta::Process = new FiestaProcess();

extern ExtraMenuTextures* extraMenuTextures = new ExtraMenuTextures();

DWORD WINAPI Fiesta::Install(LPVOID lpParameter)
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

	extraMenuTextures->Initialize(Process);

	int patchError = Process->PatchCode();

	if (patchError > 0)
	{
		char patchErrorMessage[256];
		sprintf_s(patchErrorMessage, 256, "There was an error patching Fiesta. Error Code %d", patchError);

		MessageBox(NULL, patchErrorMessage, "Fiesta", MB_ICONERROR);

		return 0;
	}

	bool hookError = Process->InstallDetours();

	if (hookError)
	{
		char hookErrorMessage[256];
		sprintf_s(hookErrorMessage, 256, "There was an error modifying Fiesta. Error Code %d", hookError);

		MessageBox(NULL, hookErrorMessage, "Fiesta", MB_ICONERROR);

		return 0;
	}

	return 0;
}