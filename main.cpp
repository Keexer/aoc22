#include "Days/Day1.h"
#include "frwk/DaysHandler.h"

int main()
{
	Day1 day1;

	auto calories = day1.extract();
	day1.presentA(calories);
	day1.presentB(calories);

	DaysHandler handler;
	handler.addDay(Day1{});
}