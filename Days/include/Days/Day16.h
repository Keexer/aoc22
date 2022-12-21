#pragma once

#include <vector>

class Day16
{
public:
  struct Report
  {
    size_t origin{};
    std::vector<size_t> paths{};
    uint32_t flowRate{0};
    bool valveOpen{false};
  };

  using Data = std::vector<Report>;
  Data extract();
  void solveA(Data& data);
  void solveB(Data& data);
  void solve();
};