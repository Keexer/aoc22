#pragma once

#include <fstream>
#include <vector>

class Day1
{
public:
	Day1() = default;
	std::vector<int> extract();
	void presentA(std::vector<int>& vec);
	void presentB(std::vector<int>& vec);
	void solve();
};