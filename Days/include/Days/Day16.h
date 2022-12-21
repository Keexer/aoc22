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
    std::unordered_map<std::string, size_t> flowRate2{};
    std::unordered_multimap<std::string, std::string> neighbours{};
    std::unordered_set<std::string> usefulValves{};
    std::unordered_map<std::string, std::unordered_map<std::string, size_t> > steps{};

    size_t origin{};
    std::vector<size_t> paths{};
    uint32_t flowRate{0};
    bool valveOpen{false};
  };

  using Data = Report;
  Data extract();
  void solveA(Data& data);
  void solveB(Data& data);
  void solve();
};