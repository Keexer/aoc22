#include "Days/Day12.h"

#include <fstream>
#include <sstream>
#include <queue>
#include <iostream>
#include <limits>
#include <optional>

namespace
{

std::optional<int> getShortestPath(Data& input)
{
  std::vector<std::vector<std::optional<int> > > steps;

  for (size_t i = 0; i < input.map.size(); ++i)
  {
    std::vector<std::optional<int> > row(input.map.front().size(), std::optional<int>{});
    steps.push_back(row);
  }

  struct Node
  {
    int row{};
    int col{};
    int steps{};
  };

  std::queue<Node> nodeQueue{};
  nodeQueue.push({ input.start.first, input.start.second, 0 });
  steps.at(input.start.first).at(input.start.second) = 0;

  const int lastRowIndex = static_cast<int>(input.map.size()) - 1;
  const int lastColIndex = static_cast<int>(input.map.front().size()) - 1;

  while (true)
  {
    if (nodeQueue.empty())
    {
      return {};
    }

    auto current = nodeQueue.front();
    nodeQueue.pop();

    // up
    if (current.row > 0) // check that we don't try to access an index out of bounds
    {
      const int oneRowUp = current.row - 1;
      if (!steps.at(oneRowUp).at(current.col)) // If step[row][col] is already set there is a shorter path
      {
        if (input.map.at(oneRowUp).at(current.col) <= input.map.at(current.row).at(current.col) + 1) // Check that the elevation is at maximum one step higher
        {
          const int newSteps = current.steps + 1;
          steps.at(oneRowUp).at(current.col) = newSteps;
          nodeQueue.push({ oneRowUp, current.col, newSteps }); // Push this neighbour node on the queue
        }
      }
    }
    // down
    if (current.row < lastRowIndex)
    {
      const int oneRowDown = current.row + 1;
      if (!steps.at(oneRowDown).at(current.col))
      {
        if (input.map.at(oneRowDown).at(current.col) <= input.map.at(current.row).at(current.col) + 1)
        {
          int newSteps = current.steps + 1;
          steps.at(oneRowDown).at(current.col) = newSteps;
          nodeQueue.push({ oneRowDown, current.col, newSteps });
        }
      }
    }
    // left
    if (current.col > 0)
    {
      const int oneColLeft = current.col - 1;
      if (!steps.at(current.row).at(oneColLeft))
      {
        if (input.map.at(current.row).at(oneColLeft) <= input.map.at(current.row).at(current.col) + 1)
        {
          int newSteps = current.steps + 1;
          steps.at(current.row).at(oneColLeft) = newSteps;
          nodeQueue.push({ current.row, oneColLeft, newSteps });
        }
      }
    }
    // right
    if (current.col < lastColIndex)
    {
      const int oneColRight = current.col + 1;
      if (!steps.at(current.row).at(oneColRight))
      {
        if (input.map.at(current.row).at(oneColRight) <= input.map.at(current.row).at(current.col) + 1)
        {
          int newSteps = current.steps + 1;
          steps.at(current.row).at(oneColRight) = newSteps;
          nodeQueue.push({ current.row, oneColRight, newSteps });
        }
      }
    }

    if (auto shortest = steps.at(input.end.first).at(input.end.second); shortest)
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
        data.start = { static_cast<int>(data.map.size()), static_cast<int>(row.size()) };
        row.push_back(1);
      }
      else if (c == 'E')
      {
        data.end = { static_cast<int>(data.map.size()), static_cast<int>(row.size()) };
        row.push_back('z' - 'a' + 1);
      }
      else if (c == 'a')
      {
        data.elevationA.push_back({ static_cast<int>(data.map.size()), static_cast<int>(row.size()) });
        row.push_back(c - 'a' + 1);
      }
      else if (c == '\r')
      {
        // On linux (wsl) ignore carriage return
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
  if (auto r = getShortestPath(input); r)
  {
    std::cout << "Shortest steps to E: " << *r << '\n';
  }
  else
  {
    std::cout << "No solution found\n";
  }
}

void Day12::solveB(Data& input)
{
  std::optional<int> shortest{};
  input.elevationA.push_back(input.start);
  for (std::vector<std::pair<int, int> >::iterator it = input.elevationA.begin(); it != input.elevationA.end();)
  {
    input.start = *it;
    auto r = getShortestPath(input);
    if (r && ((*r < shortest) || !shortest))
    {
      shortest = *r;
    }
    it = input.elevationA.erase(it);
  }

  if (shortest)
  {
    std::cout << "Shortest steps from any a to E: " << *shortest << '\n';
  }
  else
  {
    std::cout << "No solution found\n";
  }
}

void Day12::solve()
{
  auto input = extract();
  solveA(input);
  solveB(input);
}
