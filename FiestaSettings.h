#pragma once

#include "Villain\Settings.h"

#define LoadSettings_Success				0
#define LoadSettings_File_Not_Found			1

class FiestaSettings : public Settings
{
	private:
		HMODULE _dllInstance;

		bool _customClassesEnabled;

	public:
		int LoadSettings(char* iniPath);

		void SetDllInstance(HMODULE const& hModule)
		{
			_dllInstance = hModule;
		}

		HMODULE GetDllInstance()
		{
			return _dllInstance;
		}

		bool GetCustomClassesEnabled()
		{
			return _customClassesEnabled;
		}

		void SetCustomClassesEnabled(LPSTR const& value)
		{
			_customClassesEnabled = ParseBoolean(value);
		}

		void SetCustomClassesEnabled(bool value)
		{
			_customClassesEnabled = value;
		}
};