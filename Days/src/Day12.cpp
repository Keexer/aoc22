#include "Days/Day12.h"

#include <fstream>
#include <sstream>
#include <queue>
#include <iostream>
#include <limits>

namespace
{

int getShortestPath(Data& input)
{
  std::vector<std::vector<int> > steps;

  for (size_t i = 0; i < input.map.size(); ++i)
  {
    std::vector<int> row(input.map.front().size(), -1);
    steps.push_back(row);
  }

  struct Node
  {
    int x{};
    int y{};
    int steps{};
  };

  std::queue<Node> nodeQueue{};
  nodeQueue.push({ input.start.second, input.start.first, 0 });
  steps.at(input.start.first).at(input.start.second) = 0;

  while (true)
  {
    if (nodeQueue.empty())
    {
      return steps.at(input.end.first).at(input.end.second);
    }

    auto current = nodeQueue.front();
    nodeQueue.pop();

    // up
    if (current.y > 0)
    {
      if (steps.at(current.y - 1).at(current.x) == -1)
      {
        if (input.map.at(current.y - 1).at(current.x) <= input.map.at(current.y).at(current.x) + 1)
        {
          int newSteps = current.steps + 1;
          steps.at(current.y - 1).at(current.x) = newSteps;
          nodeQueue.push({ current.x, current.y - 1, newSteps });
        }
      }
    }
    // down
    if (current.y + 1 < static_cast<int>(input.map.size()))
    {
      if (steps.at(current.y + 1).at(current.x) == -1)
      {
        if (input.map.at(current.y + 1).at(current.x) <= input.map.at(current.y).at(current.x) + 1)
        {
          int newSteps = current.steps + 1;
          steps.at(current.y + 1).at(current.x) = newSteps;
          if (current.y + 1 < static_cast<int>(input.map.size()))
          {
            nodeQueue.push({ current.x, current.y + 1, newSteps });
          }
        }
      }
    }
    // left
    if (current.x > 0)
    {
      if (steps.at(current.y).at(current.x - 1) == -1)
      {
        if (input.map.at(current.y).at(current.x - 1) <= input.map.at(current.y).at(current.x) + 1)
        {
          int newSteps = current.steps + 1;
          steps.at(current.y).at(current.x - 1) = newSteps;
          nodeQueue.push({ current.x - 1, current.y, newSteps });
        }
      }
    }
    // right
    if (current.x + 1 < static_cast<int>(input.map.front().size()))
    {
      if (steps.at(current.y).at(current.x + 1) == -1)
      {
        if (input.map.at(current.y).at(current.x + 1) <= input.map.at(current.y).at(current.x) + 1)
        {
          int newSteps = current.steps + 1;
          steps.at(current.y).at(current.x + 1) = newSteps;
          if (current.x + 1 < static_cast<int>(input.map.front().size()))
          {
            nodeQueue.push({ current.x + 1, current.y, newSteps });
          }
        }
      }
    }

    if (int shortest = steps.at(input.end.first).at(input.end.second); shortest > 0)
    {
      return shortest;
    }
  }
}

}

Data Day12::extract()
{
  std::ifstream file{"../../Input/Input12.txt"};

  if (!file.is_open())
  {
    return {};
  }

  std::string line;
  Data data{};

  while (std::getline(file, line))
  {
    std::vector<int> row;
    for (auto c : line)
    {
      if (c == 'S')
      {
        data.start = {static_cast<int>(data.map.size()), static_cast<int>(row.size())};
        row.push_back(1);
      }
      else if (c == 'E')
      {
        data.end = { static_cast<int>(data.map.size()), static_cast<int>(row.size()) };
        row.push_back('z' - 'a' + 1);
      }
      else if (c == 'a')
      {
        data.elevationA.push_back({static_cast<int>(data.map.size()), static_cast<int>(row.size())});
        row.push_back(c - 'a' + 1);
      }
      else if (c == '\r')
      {
        // On linux ignore carriage return
      }
      else
      {
        row.push_back(c - 'a' + 1);
      }
    }
    data.map.push_back(row);
  }

  return data;
}

void Day12::solveA(Data& input)
{
  auto shortest = getShortestPath(input);
  std::cout << "Shortest steps to E: " << shortest << '\n';
}

void Day12::solveB(Data& input)
{
  int shortest{std::numeric_limits<int>::max()};
  input.elevationA.push_back(input.start);
  for (std::vector<std::pair<int, int> >::iterator it = input.elevationA.begin(); it != input.elevationA.end();)
  {
    input.start = *it;
    auto steps = getShortestPath(input);
    if (steps >= 0 && steps < shortest)
    {
      shortest = steps;
    }
    it = input.elevationA.erase(it);
  }

  std::cout << "Shortest steps from any a to E: " << shortest << '\n';
}

void Day12::solve()
{
  auto input = extract();
  solveA(input);
  solveB(input);
}
