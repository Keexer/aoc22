#include "Days/Day1.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <string>
#include <fstream>

std::vector<int> Day1::extract()
{
	std::ifstream file;
	file.open("../../Input/Input1.txt");

	if (!file.is_open())
	{
		return {};
	}

	std::vector<int> calories {};
	std::string line {};
	int val {0};

	while (std::getline(file, line))
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

	file.close();

	std::sort(calories.begin(), calories.end(), [](auto const& a, auto const& b)
		{
			return a > b;
		});

	return calories;
}

void Day1::presentA(std::vector<int>& vec)
{
	std::cout << "First task: Max calories = " << vec.front() << '\n';
}

void Day1::presentB(std::vector<int>& vec)
{
	int sum = std::accumulate(vec.begin(), vec.begin() + 3, 0);
	std::cout << "Second task: Three max calories = " << sum << '\n';
}

void Day1::solve()
{
	auto data = extract();
	presentA(data);
	presentB(data);
}
