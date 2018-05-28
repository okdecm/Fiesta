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
string GetTexturePath(int id);