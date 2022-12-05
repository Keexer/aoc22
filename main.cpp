#include "Days/Day1.h"
#include "Days/Day2.h"
#include "Days/Day3.h"
#include "Days/Day4.h"
#include "Days/Day5.h"
#include "frwk/DaysHandler.h"
#include "frwk/StartInfo.h"

int main()
{
	DaysHandler handler;

	handler.addDay(Day1{}, 1);
	handler.addDay(Day2{}, 2);
	handler.addDay(Day3{}, 3);
	handler.addDay(Day4{}, 4);
	handler.addDay(Day5{}, 5);

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