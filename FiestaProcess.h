#pragma once

#include "Villain\Process.h"

class FiestaProcess : public Process
{
	public:
		virtual void OnPatchCode(HANDLE process);
		virtual void OnInstallDetours();
};