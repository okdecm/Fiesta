#include "CustomClasses.h"

#include "Villain\Generic.h"

#include "Fiesta.h"

#include "Hooks\CreateClass\CharCreateClassWin_Create_Button.h"

bool CustomClasses::Initialize(Process* process)
{
	char jsonPath[MAX_PATH] = { 0 };
	sprintf_s(jsonPath, "%sCustomClasses.json", Fiesta::Process->GetDirectory());

	if (!FileExists(jsonPath))
	{
		MessageBox(nullptr, "Could not find \"CustomClasses.json\"", "Fiesta", MB_ICONERROR);

		return false;
	}

	try
	{
		Classes = CustomClass::DeserializeFromJSONFile(jsonPath);
	}
	catch (...)
	{
		MessageBox(nullptr, "Failed to read file \"CustomClasses.json\"", "Fiesta", MB_ICONERROR);

		return false;
	}

	AddHook(new CharCreateClassWin_Create_Button());

	return Modification::Initialize(process);
}