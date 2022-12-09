#pragma once

#include <vector>
#include <utility>

class Day9
{
public:
  using Instructions = std::vector<std::pair<char, uint8_t> >;

  Instructions extract();
  void solveA(Instructions& inst);
  void solveB(Instructions& inst);
  void solve();
};