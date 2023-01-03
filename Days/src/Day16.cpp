#include "Days/Day16.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>

namespace
{

class Dfs
{
public:
  size_t DFS(Day16::Report& r, std::string current, size_t time, size_t total, std::unordered_set<std::string>& open)
  {
    static constexpr size_t minutes = 30;
    size_t max = total + getFlow(r.flowRate, open) * (minutes - time);

    for (auto next : r.usefulValves)
    {
      if (open.contains(next))
      {
        continue;
      }

      size_t timeDelta = r.steps[current][next] + 1;

      if (time + timeDelta >= minutes)
      {
        continue;
      }

      size_t newTotal = total + timeDelta * getFlow(r.flowRate, open);
      open.insert(next);
      size_t value = DFS(r, next, time + timeDelta, newTotal, open);
      if (max < value)
      {
        max = value;
      }
      open.erase(next);
    }

    return max;
  }

  size_t dfs_elephant(Day16::Report& r, std::string current, bool elephant, int64_t time, int64_t total, std::unordered_set<std::string>&open, const std::unordered_set<std::string>&useful)
  {
    static constexpr int64_t minutes = 26;
    // If we do nothing the maximum is: current total + flow from all opened valves * remaining time
    size_t max = total + getFlow(r.flowRate, open) * (minutes - time);
    // But if we are us, we can let loose an elephant
    if (!elephant) {
      // The elephant can only open valves that we haven't open yet.
      std::unordered_set<std::string> new_candidates = useful;
      for (auto& v : open) new_candidates.erase(v);

      std::unordered_set<std::string> new_open;
      // Let the elephant run around from "AA" at time zero
      size_t max_elephant = dfs_elephant(r, "AA", true, 0, 0, new_open, new_candidates);
      max = total + getFlow(r.flowRate, open) * (minutes - time) + max_elephant;
    }
    for (auto& next : useful) {
      // moving to this valve is useless, as it is already open
      if (open.contains(next))
        continue;

      int64_t time_delta = r.steps[current][next] + 1;
      // moving to this valve and opening it would take more time than we have
      if (time + time_delta >= minutes)
        continue;

      // the flow as we move to the next valve and open it
      int64_t new_total = total + time_delta * getFlow(r.flowRate, open);
      open.insert(next);
      // recurse with this valve open, if it is an improvement, remember
      // importantly, this path is common for both the us and the elephant
      size_t value = dfs_elephant(r, next, elephant, time + time_delta, new_total, open, useful);
      if (max < value) max = value;
      open.erase(next);
    }
    return max;
  }

private:
  int64_t getFlow(std::unordered_map<std::string, int64_t> flow, std::unordered_set<std::string> open)
  {
    int64_t sum{};
    for (auto v : open)
    {
      sum += flow[v];
    }

    return sum;
  }

  Day16::Data mData;
  std::vector<std::vector<size_t> > mSteps;
  std::set<size_t> mPossibleValves;
};

auto floydWarshall(std::unordered_set<std::string> valves, std::unordered_multimap<std::string, std::string> neighbours)
{
  std::unordered_map<std::string, std::unordered_map<std::string, int64_t>> distance;
  for (auto& from : valves)
  {
    for (auto& to : valves)
    {
      distance[from][to] = static_cast<int64_t>(valves.size()) + 1;
    }
  }

  for (auto& [from, to] : neighbours)
  {
    distance[from][to] = 1;
  }
  
  for (auto& from : valves)
  {
    distance[from][from] = 0;
  }
  
  for (auto& via : valves)
  {
    for (auto& from : valves)
    {
      for (auto& to : valves)
      {
        if (distance[from][to] > distance[from][via] + distance[via][to])
          distance[from][to] = distance[from][via] + distance[via][to];
      }
    }
  }

  return distance;
}

}

Day16::Data Day16::extract()
{
  std::ifstream file{ "../../Input/Input16.txt" };

  if (!file.is_open())
  {
    return {};
  }

  std::string line;
  Report r;

  while (std::getline(file, line))
  {
    static constexpr size_t startOfValve = 6;

    std::string valve = line.substr(startOfValve, 2);

    r.valves.insert(valve);
    std::string flow = line.substr(line.find("=") + 1, line.find(";"));
    r.flowRate[valve] = std::stoi(flow);

    line = line.erase(0, line.find("valve") + sizeof("valve"));
    if (line.at(0) == ' ')
    {
      line = line.erase(0, 1);
    }

    while (true)
    {
      size_t comma = line.find(",");
      if (comma == std::string::npos)
      {
        std::string lastLine = line.substr(0, 2);
        // add last
        r.neighbours.insert(std::make_pair(valve, lastLine));
        break;
      }
      r.neighbours.insert(std::make_pair(valve, line.substr(0, comma)));
      line = line.erase(0, comma + 2);
    }
  }

  for (auto v : r.flowRate)
  {
    if (v.second > 0)
    {
      r.usefulValves.insert(v.first);
    }
  }

  r.steps = floydWarshall(r.valves, r.neighbours);

  return r;
}

void Day16::solveA(Data& data)
{
  Dfs d;
  std::unordered_set<std::string> open;
  size_t sum = d.DFS(data, "AA", 0, 0, open);

  std::cout << "Total pressure released: " << sum << '\n';
}

void Day16::solveB(Data& data)
{
  Dfs d;
  std::unordered_set<std::string> open;
  size_t sum = d.dfs_elephant(data, "AA", false, 0, 0, open, data.usefulValves);

  std::cout << "Pressured release with help from an elephant: " << sum << '\n';
}

void Day16::solve()
{
  auto data = extract();
  solveA(data);
  solveB(data);
}
