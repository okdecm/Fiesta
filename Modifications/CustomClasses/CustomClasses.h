#pragma once

#include <vector>

#include "Villain\Modification.h"

#include "CustomClass.h"

class CustomClasses : public Modification
{
	public:
		vector<CustomClass> Classes;

		bool Initialize(Process* process);
};