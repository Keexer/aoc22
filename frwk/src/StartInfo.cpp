#include "frwk/StartInfo.h"

#include <iostream>

StartInfo::StartInfo(DaysHandler& handler)
{
	std::cout << "Welcome!\n\n" << "Choose solution\n\n";
	for (int i = 1; i < 26; i++)
	{
		std::cout << "Day: " << i;
		if (handler.exist(i))
		{
			std::cout << " = Solved\n";
		}
		else
		{
			std::cout << " = Not solved\n";
		}
	}
}

void StartInfo::printIntro()
{
}

int StartInfo::getInput()
{
	int index{};
	while (true)
	{
		std::cout << "\nWhich day to present? (0 to exit) ";
		std::cin >> index;

		if (index <= 25)
		{
			std::cout << "\n######################\nPresenting result for day " << index << "\n";
			break;
		}
		else
		{
			std::cout << "\n######################\nNo problem for that day\n######################\n";
		}
	}

	return index;
}
