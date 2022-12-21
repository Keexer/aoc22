#include "Days/Day16.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <unordered_set>

namespace
{

static constexpr auto INF = std::numeric_limits<size_t>::max();

std::vector<size_t> getSteps(std::vector<std::vector<size_t> > steps, size_t current, size_t target)
{
  std::vector<size_t> path{};
  while (current != target)
  {
    current = steps[current][target];
    path.push_back(current);
  }

  return path;
}

class Dfs
{
public:
  Dfs(Day16::Data data, std::vector<std::vector<size_t> > steps)
    : mData(data)
    , mSteps(steps)
  {
    for (auto i = 0; i < data.size(); ++i)
    {
      if (data[i].flowRate > 0)
      {
        mPossibleValves.insert(i);
      }
    }
  }

  size_t DFS(size_t current, size_t time, size_t total, std::unordered_set<size_t>& open)
  {
    size_t max = total + getFlow(open) * (30 - time);

    for (auto next : mPossibleValves)
    {
      if (open.contains(next))
      {
        continue;
      }

      size_t timeDelta = mSteps[current][next] + 1;

      if (time + timeDelta >= 30)
      {
        continue;
      }

      size_t newTotal = total + timeDelta * getFlow(open);
      open.insert(next);
      size_t value = DFS(next, time + timeDelta, newTotal, open);
      if (max < value)
      {
        max = value;
      }
      open.erase(next);
    }

    return max;
  }

private:
  size_t getFlow(std::unordered_set<size_t> open)
  {
    size_t sum{};
    for (auto v : open)
    {
      sum += mData.at(v).flowRate;
    }

    return sum;
  }

  Day16::Data mData;
  std::vector<std::vector<size_t> > mSteps;
  std::set<size_t> mPossibleValves;
};

std::vector<std::vector<size_t> > createGraph(Day16::Data& data)
{
  std::vector<size_t> row(data.size(), INF);
  std::vector<std::vector<size_t> > graph(data.size(), row);

  for (size_t i = 0; i < data.size(); ++i)
  {
    for (size_t j = 0; j < data[i].paths.size(); ++j)
    {
      for (int k = 0; k < data.size(); ++k)
      {
        if (data[k].origin == data[i].paths[j])
        {
          if (!data[k].valveOpen)
          {
            graph[i][k] = data[k].flowRate;
          }
          else
          {
            graph[i][k] = 0;
          }
        }
      }
    }
    graph[i][i] = 0;
  }

  return graph;
}

std::vector<std::vector<size_t> > findMostValuePath(std::vector<std::vector<size_t> >& graph)
{
  std::vector<size_t> cols(graph.front().size(), 0);
  std::vector<std::vector<size_t> > steps{graph.size(), cols};

  for (size_t i = 0; i < steps.front().size(); ++i)
  {
    for (size_t j = 0; j < steps.size(); ++j)
    {
      steps[i][j] = j;
    }
  }

  for (size_t k = 0; k < graph.size(); ++k)
  {
    for (size_t i = 0; i < graph.size(); ++i)
    {
      for (size_t j = 0; j < graph.size(); ++j)
      {
        if (graph[i][j] > (graph[i][k] + graph[k][j])
          && (graph[k][j] != INF
            && graph[i][k] != INF))
        {
          graph[i][j] = graph[i][k] + graph[k][j];
steps[i][j] = steps[i][k];
        }
      }
    }
  }

  return steps;
}

}

Day16::Data Day16::extract()
{
  Data ret{};

  std::ifstream file{ "../../Input/Input16.txt" };

  if (!file.is_open())
  {
    return {};
  }

  std::string line;

  while (std::getline(file, line))
  {
    Report r;
    r.valveOpen = false;

    r.origin = std::hash<std::string>{}(line.substr(6, 2));
    r.flowRate = std::stoi(line.substr(line.find("=") + 1, line.find(";")));

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
        // add last
        r.paths.push_back(std::hash<std::string>{}(line));
        break;
      }
      r.paths.push_back(std::hash<std::string>{}(line.substr(0, comma)));
      line = line.erase(0, comma + 2);
    }

    ret.push_back(r);
  }

  return ret;
}

void Day16::solveA(Data& data)
{
  // Create graph
  auto graph = createGraph(data);

  // Find shortest path
  auto steps = findMostValuePath(graph);

  std::vector<std::vector<size_t> > allSteps;

  for (size_t i = 0; i < graph.size(); i++)
  {
    std::vector<size_t> temp;
    for (size_t j = 0; j < graph.size(); j++)
    {
      auto r = getSteps(steps, i, j);
      temp.push_back(r.size());
    }
    allSteps.push_back(temp);
  }

  Dfs dfs(data, allSteps);

  size_t startIndex{};

  for (int i = 0; i < data.size(); ++i)
  {
    if (data[i].origin == std::hash<std::string>{}("AA"))
    {
      startIndex = i;
      break;
    }
  }

  std::unordered_set<size_t> open;
  auto sum = dfs.DFS(startIndex, 0, 0, open);

  std::cout << "Total pressure released: " << sum << '\n';

  int t = 0;
}

void Day16::solveB(Data& data)
{
}

void Day16::solve()
{
  auto data = extract();
  solveA(data);
  solveB(data);
}
