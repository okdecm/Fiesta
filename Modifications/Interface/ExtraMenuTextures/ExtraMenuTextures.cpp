#include <ThirdParty\Json\json.hpp>
#include <fstream>
#include <string>

#include "ExtraMenuTextures.h"

#include "Villain\Generic.h"

#include "Fiesta.h"

#include "Hooks\MenuTexMgr_GetTexture_UpdateLimit.h"
#include "Hooks\MenuTexMgr_Create_GetTexturePath.h"
#include "Hooks\MenuTexMgr_GetTexture_Check.h"
#include "Hooks\MenuTexMgr_GetTexture_Set.h"
#include "Hooks\MenuTexMgr_GetTexture_SetReturn.h"

using namespace std;
using json = nlohmann::json;

map<int, string> extraTextures = {};
map<int, DWORD> extraTexturesLoadedAt = {};

bool ExtraMenuTextures::Initialize(Process* process)
{
	char jsonPath[MAX_PATH] = { 0 };
	sprintf_s(jsonPath, "%sExtraMenuTextures.json", Fiesta::Process->GetDirectory());

	if (!FileExists(jsonPath))
	{
		MessageBox(nullptr, "Could not find \"ExtraMenuTextures.json\"", "Fiesta", MB_ICONERROR);

		return false;
	}

	try
	{
		ifstream stream(jsonPath);
		json jsonData = json::parse(stream);

		for (json::iterator iterator = jsonData.begin(); iterator != jsonData.end(); ++iterator) {
			int key = stoi(iterator.key());
			string value = iterator.value();

			extraTextures.insert(pair<int, string>(key, value));
			extraTexturesLoadedAt.insert(pair<int, DWORD>(key, 0x0));
		}

		stream.close();
	}
	catch (...)
	{
		MessageBox(nullptr, "Failed to read file \"ExtraMenuTextures.json\"", "Fiesta", MB_ICONERROR);

		return false;
	}

	AddHook(new MenuTexMgr_GetTexture_UpdateLimit());
	AddHook(new MenuTexMgr_Create_GetTexturePath());
	AddHook(new MenuTexMgr_GetTexture_Check());
	AddHook(new MenuTexMgr_GetTexture_Set());
	AddHook(new MenuTexMgr_GetTexture_SetReturn());

	return Modification::Initialize(process);
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