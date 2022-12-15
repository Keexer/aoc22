#pragma once

#include <vector>
#include <utility>
#include <cstdint>

class Day15
{
public:
  struct Coords
  {
    int64_t x;
    int64_t y;
  };

  struct Beacon : public Coords
  {};

  struct Sensor : public Coords
  {};

  using Data = std::vector<std::pair<Sensor, Beacon> >;
  Data extract();
  void solveA(Data& data);
  void solveB(Data& data);
  void solve();
};