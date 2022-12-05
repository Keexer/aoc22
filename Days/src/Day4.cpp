#include "Days/Day4.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

Day4::Container Day4::extract()
{
  std::ifstream file;
  file.open("../../Input/Input4.txt");

  if (!file.is_open())
  {
    return {};
  }

  std::vector<std::vector<std::pair<int, int> > > pairList;
  std::string line;
  while (std::getline(file, line))
  {
    std::string first = line.substr(0, line.find(','));
    std::string second = line.substr(line.find(',') + 1);
    std::pair firstPair = { std::stoi(first.substr(0, first.find('-'))), std::stoi(first.substr(first.find('-') + 1)) };
    std::pair secondPair = { std::stoi(second.substr(0, second.find('-'))), std::stoi(second.substr(second.find('-') + 1)) };
    pairList.push_back({ firstPair, secondPair });
  }

  return pairList;
}

void Day4::solveA(Day4::Container cont)
{
  int overlappings{};
  for (auto v : cont)
  {
    // check first
    if ((v[0].first >= v[1].first) && (v[0].second <= v[1].second))
    {
      ++overlappings;
      continue;
    }
    // check second
    if ((v[1].first >= v[0].first) && (v[1].second <= v[0].second))
    {
      ++overlappings;
    }
  }

  std::cout << "Overlapping assignments: " << overlappings << '\n';
}

void Day4::solveB(Day4::Container cont)
{
  int overlappings{};
  for (auto v : cont)
  {
    // check first
    if (v[0].first <= v[1].second && v[0].second >= v[1].first)
    {
      ++overlappings;
    }
  }

  std::cout << "Any overlapping assignements: " << overlappings << '\n';
}

void Day4::solve()
{
  auto cont = extract();
  solveA(cont);
  solveB(cont);
}
