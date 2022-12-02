#include "Days/Day1.h"
#include "Days/Day2.h"
#include "frwk/DaysHandler.h"

int main()
{
	DaysHandler handler;
	handler.addDay(Day1{}, 1);

	handler.solveDay(2);
}