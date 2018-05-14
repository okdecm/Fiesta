#pragma once

#include <windows.h>

class Settings
{
	public:
		bool ParseBoolean(LPSTR const& boolStr)
		{
			if ((_strcmpi(boolStr, "true") == 0) || (_strcmpi(boolStr, "1") == 0))
			{
				return true;
			}

			return false;
		}
};