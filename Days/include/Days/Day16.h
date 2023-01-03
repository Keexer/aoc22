#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

class Day16
{
public:
  struct Report
  {
    std::unordered_set<std::string> valves{};
    std::unordered_map<std::string, int64_t> flowRate{};
    std::unordered_multimap<std::string, std::string> neighbours{};
    std::unordered_set<std::string> usefulValves{};
    std::unordered_map<std::string, std::unordered_map<std::string, int64_t> > steps{};
  };

  using Data = Report;
  Data extract();
  void solveA(Data& data);
  void solveB(Data& data);
  void solve();
};