#pragma once

#include <utility>
#include <vector>

struct Data
{
  std::pair<int, int> start;
  std::pair<int, int> end;
  std::vector<std::vector<int> > map;
  std::vector<std::pair<int, int> > elevationA;
};

class Day12
{
public:
  Data extract();
  void solveA(Data& input);
  void solveB(Data& input);
  void solve();
};