#pragma once

#include <vector>
#include <utility>
#include <stack>

class Day5
{
public:
  struct CrateStack
  {
    std::vector<std::stack<char> > crateStack;
  };

  struct Instructions
  {
    int move;
    int from;
    int to;
  };

  struct Return
  {
    CrateStack stack;
    std::vector<Instructions> instructions;
  };

  Return extract();
  void solveA(Return ret);
  void solveB(Return ret);
  void solve();
};
