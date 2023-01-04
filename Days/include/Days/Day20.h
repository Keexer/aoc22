#pragma once

#include <vector>
#include <cstdint>

class Day20
{
public:
  using Data = std::vector<int64_t>;
  Data extract();
  void solveA(Data data);
  void solveB(Data data);
  void solve();

private:
  void moveValue(Data& transform, int64_t steps, int64_t currentPos);
};