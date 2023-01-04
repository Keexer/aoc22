#pragma once

#include <vector>

class Day20
{
public:
  using Data = std::vector<int>;
  Data extract();
  void solveA(Data data);
  void solveB(Data data);
  void solve();

private:
  void moveValue(std::vector<int>& transform, int steps, int currentPos);
};