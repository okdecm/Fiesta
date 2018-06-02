#include "ExtraMenuTextures.h"

#include "Hooks\MenuTexMgr_GetTexture_UpdateLimit.h"
#include "Hooks\MenuTexMgr_Create_GetTexturePath.h"
#include "Hooks\MenuTexMgr_GetTexture_Check.h"
#include "Hooks\MenuTexMgr_GetTexture_Set.h"
#include "Hooks\MenuTexMgr_GetTexture_SetReturn.h"

using namespace std;

map<int, string> extraTextures = {
	{0x21, "Common/Loading"}
};

map<int, DWORD> extraTexturesLoadedAt = {
	{0x21, 0x00000000}
};

void ExtraMenuTextures::Initialize(Process* process)
{
	AddHook(new MenuTexMgr_GetTexture_UpdateLimit());
	AddHook(new MenuTexMgr_Create_GetTexturePath());
	AddHook(new MenuTexMgr_GetTexture_Check());
	AddHook(new MenuTexMgr_GetTexture_Set());
	AddHook(new MenuTexMgr_GetTexture_SetReturn());

	Modification::Initialize(process);
}

bool ExtraTextureExists(int id)
{
	return extraTextures.find(id) != extraTextures.end();
}

char* GetTexturePath(int id)
{
	string texturePath = extraTextures.find(id)->second;
	char* cstr = new char[texturePath.length() + 1];

	strcpy(cstr, texturePath.c_str());

	return cstr;
}

DWORD GetLoadedTexturePointer(int id)
{
	return extraTexturesLoadedAt.find(id)->second;
}

void SetLoadedTexturePointer(int id, DWORD value)
{
	extraTexturesLoadedAt.find(id)->second = value;
}