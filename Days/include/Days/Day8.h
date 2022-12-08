#pragma once

#include <vector>
#include <stdint.h>

class Day8
{
public:
  using Matrix = std::vector<std::vector<uint8_t> >;
  Matrix extract();
  void solveA(Matrix& input);
  void solveB(Matrix& input);
  void solve();
};