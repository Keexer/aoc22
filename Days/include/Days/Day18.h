#pragma once

#include <vector>

class Day18
{
public:
  enum class NodeType
  {
    AIR,
    LAVA,
    WATER
  };

  struct Cube
  {
    int x;
    int y;
    int z;
  };

  using Data = std::vector<Cube>;
  Data extract();
  void solveA(Data&);
  void solveB(Data&);
  void solve();
};
