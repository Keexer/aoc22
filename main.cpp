#include "Days/Day1.h"
#include "Days/Day2.h"
#include "Days/Day3.h"
#include "Days/Day4.h"
#include "Days/Day5.h"
#include "Days/Day6.h"
#include "Days/Day7.h"
#include "Days/Day8.h"
#include "Days/Day9.h"
#include "frwk/DaysHandler.h"
#include "frwk/StartInfo.h"

int main()
{
	DaysHandler handler;

	handler.addDay(Day1{}, 1);
	handler.addDay(Day2{}, 2);
	handler.addDay(Day3{}, 3);
	handler.addDay(Day4{}, 4);
	handler.addDay(Day5{}, 5); // NOLINT
	handler.addDay(Day6{}, 6); // NOLINT
	handler.addDay(Day7{}, 7); // NOLINT
	handler.addDay(Day8{}, 8); // NOLINT
	handler.addDay(Day9{}, 9); // NOLINT

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