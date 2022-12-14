#pragma once

#include <vector>

class Day14
{
public:
  struct Coordinates
  {
    int x;
    int y;
  };

  enum Point : int
  {
    STONE = 0,
    SAND,
    FREE
  };

  using Map = std::vector<std::vector<Point> >;
  using Input = std::vector<std::vector<Coordinates> >;
  using Data = std::pair<Map, Input>;
  Data extract();
  void solveA(Data input);
  void solveB(Data input);
  void solve();
};