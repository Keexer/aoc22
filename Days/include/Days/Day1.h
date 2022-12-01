#pragma once

#include <fstream>
#include <vector>

class Day1
{
public:
	Day1();
	std::vector<int> extract();
	void presentA(std::vector<int>& vec);
	void presentB(std::vector<int>& vec);

private:
	std::ifstream mFile;
};