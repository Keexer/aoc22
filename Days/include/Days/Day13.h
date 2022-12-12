#pragma once

#include <map>
#include <vector>
#include <utility>
#include <string>
#include <variant>

class Day13
{
public:
  struct Pack
  {
    std::vector<std::variant<int, Pack> > data;
  };

  using Data = std::pair<std::vector<Pack>, std::vector<Pack> >;
  
  Data extract();
  void solveA(Data& packets);
  void solveB(Data& packets);
  void solve();
};