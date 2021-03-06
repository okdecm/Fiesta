#pragma once

#include "Villain\Modification.h"

class ExtraMenuTextures : public Modification
{
	public:
		bool Initialize(Process* process);
};

map<int, string> extraTextures;
map<int, DWORD> extraTexturesLoadedAt;

bool ExtraTextureExists(int id);
char* GetTexturePath(int id);
DWORD GetLoadedTexturePointer(int id);
void SetLoadedTexturePointer(int id, DWORD value);