#pragma once

#include <windows.h>
#include <vector>

#include "Hook.h"
#include "Process.h"

using namespace std;

[event_receiver(native)]
class Modification
{
	private:
		Process* _process;
		bool _isHooked = false;
		vector<Hook*> _hooks;

	public:
		bool Initialize(Process* process);

		void PatchCode(HANDLE process);
		void InstallDetours();

		void AddHook(Hook* hook);
		
		~Modification();
};