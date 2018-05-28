#include <windows.h>

#include "Fiesta.h"

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD fwdReason, LPVOID lpvReserved)
{
	switch (fwdReason)
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hInstance);

			Sleep(10000);

			CreateThread(nullptr, 0, Fiesta::Install, hInstance, 0, nullptr);
			break;
	}

	return true;
}