#include "Days/Day1.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <string>

Day1::Day1()
{}

std::vector<int> Day1::extract()
{
	mFile.open("../../Input/Input1.txt");

	if (!mFile.is_open())
	{
		return {};
	}

	std::vector<int> calories {};
	std::string line {};
	int val {0};

	while (std::getline(mFile, line))
	{
		if (line.size() == 0 || line == "\r")
		{
			calories.push_back(val);
			val = 0;
		}
		else
		{
			val += std::stoi(line);
		}
	}

	mFile.close();

	std::sort(calories.begin(), calories.end(), [](auto const& a, auto const& b)
		{
			return a > b;
		});

	return calories;
}

void Day1::presentA(std::vector<int>& vec)
{
	std::cout << "Max calories = " << vec.front() << '\n';
}

void Day1::presentB(std::vector<int>& vec)
{
	int sum = std::accumulate(vec.begin(), vec.begin() + 3, 0);
	std::cout << "Three max calories = " << sum << '\n';
}
