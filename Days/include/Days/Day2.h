#pragma once

#include <vector>
#include <utility>

class Day2
{
public:
  Day2() = default;
  using Cont = std::vector<std::pair<char, char> >;
  Cont extract();
  void solveA(Cont& cont);
  void solveB(Cont& cont);
  void solve();
};
