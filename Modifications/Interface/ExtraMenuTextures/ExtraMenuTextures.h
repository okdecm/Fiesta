#pragma once

#include "Villain\Modification.h"

#include <vector>
#include <map>

class ExtraMenuTextures : public Modification
{
	public:
		void Initialize(Process* process);
};

bool ExtraTextureExists(int id);
char* GetTexturePath(int id);
DWORD GetLoadedTexturePointer(int id);
void SetLoadedTexturePointer(int id, DWORD value);