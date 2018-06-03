#pragma once

#include "Villain\Modification.h"

class ExtraMenuTextures : public Modification
{
	public:
		bool Initialize(Process* process);
};

bool ExtraTextureExists(int id);
char* GetTexturePath(int id);
DWORD GetLoadedTexturePointer(int id);
void SetLoadedTexturePointer(int id, DWORD value);