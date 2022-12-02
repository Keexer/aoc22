#pragma once

#include "frwk/DaysHandler.h"

class StartInfo
{
public:
	StartInfo(DaysHandler& handler);
	void printIntro();
	int getInput();
};