#include "Days/Day1.h"
#include "Days/Day2.h"
#include "Days/Day3.h"
#include "Days/Day4.h"
#include "Days/Day5.h"
#include "Days/Day6.h"
#include "Days/Day7.h"
#include "Days/Day8.h"
#include "Days/Day9.h"
#include "Days/Day10.h"
#include "Days/Day11.h"
#include "Days/Day12.h"
#include "Days/Day13.h"
#include "Days/Day14.h"
#include "Days/Day15.h"
#include "Days/Day16.h"
#include "Days/Day17.h"
#include "Days/Day18.h"
#include "Days/Day19.h"
#include "Days/Day20.h"
#include "Days/Day21.h"
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
	handler.addDay(Day10{}, 10); // NOLINT
	handler.addDay(Day11{}, 11); // NOLINT
	handler.addDay(Day12{}, 12); // NOLINT
	handler.addDay(Day13{}, 13); // NOLINT
	handler.addDay(Day14{}, 14); // NOLINT
	handler.addDay(Day15{}, 15); // NOLINT
	handler.addDay(Day16{}, 16); // NOLINT
	handler.addDay(Day17{}, 17); // NOLINT
	handler.addDay(Day18{}, 18); // NOLINT
	handler.addDay(Day19{}, 19); // NOLINT
	handler.addDay(Day20{}, 20); // NOLINT
	handler.addDay(Day21{}, 21); // NOLINT

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