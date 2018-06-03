#pragma once

#include <Windows.h>

#include <ThirdParty\Detours\Detours.h>

class Hook
{
	public:
		virtual void PatchCode(HANDLE process)
		{

		};

		virtual void InstallDetour()
		{

		};
};