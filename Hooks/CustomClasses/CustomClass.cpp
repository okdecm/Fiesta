#include <ThirdParty\Json\json.hpp>
#include <fstream>
#include <string>

#include "CustomClass.h"

using namespace std;
using json = nlohmann::json;

vector<CustomClass> CustomClass::DeserializeFromJSONFile(char* filePath)
{
	vector<CustomClass> customClasses;

	ifstream stream(filePath);
	json jsonData = json::parse(stream);

	customClasses = Deserialize(jsonData);

	stream.close();

	return customClasses;
}

vector<CustomClass> CustomClass::Deserialize(json jsonData)
{
	return Deserialize(jsonData, nullptr);
}

vector<CustomClass> CustomClass::Deserialize(json jsonData, CustomClass* parent)
{
	vector<CustomClass> customClasses;

	for (json::iterator iterator = jsonData.begin(); iterator != jsonData.end(); ++iterator) {
		try
		{
			json customClassJsonData = iterator.value();

			CustomClass customClass;
			
			customClass.ID = (unsigned int)customClassJsonData.at("ID").get<uint64_t>();
			customClass.Name = customClassJsonData.at("Name").get<string>();

			if (parent)
			{
				customClass.Parent = parent;
			}

			if (customClassJsonData.find("Children") != customClassJsonData.end())
			{
				customClass.Children = Deserialize(customClassJsonData.at("Children"), &customClass);
			}

			customClasses.push_back(customClass);
		}
		catch (...)
		{
			// Do nothing
		}
	}

	return customClasses;
}

CustomClass* CustomClass::GetBase()
{
	CustomClass* current = this;

	while (current->Parent)
	{
		current = current->Parent;
	}

	return current;
}

int CustomClass::GetHighestID()
{
	return CustomClass::GetHighestID(nullptr);
}

int CustomClass::GetHighestID(CustomClass* current)
{
	if (!current)
	{
		current = GetBase();
	}

	int highestID = current->ID;

	for (int i = 0; i < current->Children.size(); i++)
	{
		CustomClass* next = &current->Children[i];

		int idToCompare = next->GetHighestID();

		if (highestID < idToCompare)
		{
			highestID = idToCompare;
		}
	}

	return highestID;
}