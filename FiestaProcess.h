#pragma once

#include "Villain\Process.h"

class FiestaProcess : public Process
{
	void OnPatchCode(HANDLE process);
	void OnInstallDetours();
};