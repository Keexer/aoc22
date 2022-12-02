#include "Days/Day1.h"
#include "Days/Day2.h"
#include "frwk/DaysHandler.h"
#include "frwk/StartInfo.h"

int main()
{
	DaysHandler handler;

	handler.addDay(Day1{}, 1);
	handler.addDay(Day2{}, 2);

	StartInfo info(handler);
	info.printIntro();

	while (true)
	{
		int day = info.getInput();

		if (day == 0)
		{
			break;
		}

		handler.solveDay(day);

		std::cout << "######################\n";
	}
}