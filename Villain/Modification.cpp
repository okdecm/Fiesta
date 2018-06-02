#include "Modification.h"

#include "Villain\Generic.h"

void Modification::Initialize(Process* process)
{
	if(!_isHooked)
	{
		_isHooked = true;

		_process = process;

		__hook(&Process::OnPatchCode, _process, &Modification::PatchCode, this);
		__hook(&Process::OnInstallDetours, _process, &Modification::InstallDetours, this);
	}
}

void Modification::PatchCode(HANDLE process)
{
	for(std::vector<Hook*>::iterator hook = _hooks.begin(); hook != _hooks.end(); hook++)
	{
		(*hook)->PatchCode(process);
	}
}

void Modification::InstallDetours()
{
	for(std::vector<Hook*>::iterator hook = _hooks.begin(); hook != _hooks.end(); hook++)
	{
		(*hook)->InstallDetour();
	}
}

void Modification::AddHook(Hook * hook)
{
	_hooks.push_back(hook);
}

Modification::~Modification()
{
	if (_isHooked)
	{
		__unhook(&Process::OnPatchCode, _process, &Modification::PatchCode);
		__unhook(&Process::OnInstallDetours, _process, &Modification::InstallDetours);
	}
}