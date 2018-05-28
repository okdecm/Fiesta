#pragma once

#include <vector>
#include <string>
#include <ThirdParty\Json\json.hpp>

using namespace std;
using json = nlohmann::json;

class CustomClass
{
	public:
		unsigned int ID;
		string Name;

		CustomClass* Parent;
		vector<CustomClass> Children;

		static vector<CustomClass> DeserializeFromJSONFile(char* filePath);
		static vector<CustomClass> Deserialize(json jsonData);
		static vector<CustomClass> Deserialize(json jsonData, CustomClass* parent);

		CustomClass* GetBase();
		int GetHighestID();
		int GetHighestID(CustomClass* current);
};