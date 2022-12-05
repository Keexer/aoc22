#pragma once

#include <vector>

class Day4
{
public:
  using Container = std::vector<std::vector<std::pair<int, int> > >;
  Container extract();
  void solveA(Container cont);
  void solveB(Container cont);
  void solve();
};