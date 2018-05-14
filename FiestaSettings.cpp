#include <windows.h>

#include "FiestaSettings.h"

#include "Villain\Generic.h"

int FiestaSettings::LoadSettings(char* iniPath)
{
	if (!FileExists(iniPath))
	{
		return LoadSettings_File_Not_Found;
	}

	char* iniBuffer = CreateBuffer(128);

	GetPrivateProfileString("Game", "CustomClassesEnabled", "false", iniBuffer, 128, iniPath);
	SetCustomClassesEnabled(iniBuffer);

	delete[] iniBuffer;

	return LoadSettings_Success;
}