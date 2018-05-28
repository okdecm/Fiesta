#include "ExtraMenuTextures.h"

#include "Hooks\MenuTexMgr_GetTexture_UpdateLimit.h"
#include "Hooks\MenuTexMgr_Create_GetTexturePath.h"

using namespace std;

map<int, string> extraTextures = {
	{0x21, "Common/Loading"}
};

void ExtraMenuTextures::Initialize(Process* process)
{
	AddHook(new MenuTexMgr_GetTexture_UpdateLimit());
	AddHook(new MenuTexMgr_Create_GetTexturePath());

	Modification::Initialize(process);
}

bool ExtraTextureExists(int id)
{
	return extraTextures.find(id) != extraTextures.end();
}

string GetTexturePath(int id)
{
	return extraTextures.find(id)->second;
}