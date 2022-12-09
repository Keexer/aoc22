#include "Days/Day9.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

namespace
{
  static constexpr size_t MAP_SIZE = 1000;
  static constexpr size_t MAP_ORIGIN = MAP_SIZE / 2;

  using Pos = std::pair<int, int>;
  void traverseMap(char op, Pos head, Pos& tail)
  {
    static constexpr double epsilon{ 1e-10 };

    if (op == 'U' || op == 'D')
    {
      auto val = std::sqrt(std::pow((head.first - tail.first), 2) + std::pow((head.second - tail.second), 2));
      if (val > std::sqrt(2) + epsilon)
      {
        if (head.first != tail.first)
        {
          tail.first += (head.first > tail.first) ? 1 : -1;
        }
        if (head.second != tail.second)
        {
          tail.second += (head.second > tail.second) ? 1 : -1;
        }
      }
    }
    else
    {
      auto val = std::sqrt(std::pow((head.first - tail.first), 2) + std::pow((head.second - tail.second), 2));
      if (val > std::sqrt(2) + epsilon)
      {
        if (head.second != tail.second)
        {
          tail.second += (head.second > tail.second) ? 1 : -1;
        }
        if (head.first != tail.first)
        {
          tail.first += (head.first > tail.first) ? 1 : -1;
        }
      }
    }
  }

  void updateHead(char op, std::pair<int, int>& head)
  {
    if (op == 'U' || op == 'D')
      head.first += (op == 'U') ? -1 : 1;
    else
      head.second += (op == 'L') ? -1 : 1;
  }

  void present(std::vector<std::vector<bool> >& map, std::string print)
  {
    size_t visited{};

    for (auto mapRow : map)
    {
      visited += std::count(mapRow.begin(), mapRow.end(), true);
    }

    std::cout << print << visited << '\n';
  }
}

Day9::Instructions Day9::extract()
{
  std::ifstream file("../../Input/Input9.txt");

  if (!file.is_open())
  {
    return {};
  }

  std::string line{};
  char operation{};
  uint8_t steps{};
  Instructions instructions{};

  while (std::getline(file, line))
  {
    operation = line[0];
    steps = std::stoi(line.substr(line.find(' ') + 1));
    instructions.push_back({operation, steps});
  }

  return instructions;
}

void Day9::solveA(Instructions& inst)
{
  // For simplicity create a large map to traverse
  std::vector<bool> row(MAP_SIZE, false);
  std::vector<std::vector<bool> > map(MAP_SIZE, row);

  static constexpr int initial{ MAP_ORIGIN };

  std::pair<int, int> head{ initial, initial };
  std::pair<int, int> tail{ head };

  for (auto in : inst)
  {
    for (uint8_t i = 0; i < in.second; ++i)
    {
      updateHead(in.first, head);
      traverseMap(in.first, head, tail);
      map[tail.first][tail.second] = true;
    }
  }

  present(map, "Tail visited = ");
}

void Day9::solveB(Instructions& inst)
{
  // For simplicity create a large map to traverse
  std::vector<bool> row(MAP_SIZE, false);
  std::vector<std::vector<bool> > map(MAP_SIZE, row);

  static constexpr int initial{ MAP_ORIGIN };
  static constexpr int knots = 10;

  std::pair<int, int> head{ initial, initial };
  std::vector<std::pair<int, int> > tails{ knots, head }; // 0:th element is head

  for (auto in : inst)
  {
    for (uint8_t i = 0; i < in.second; ++i)
    {
      updateHead(in.first, tails.front());
      for (size_t i = 1; i < tails.size(); ++i)
      {
        traverseMap(in.first, tails[i-1], tails[i]);
      }
      map[tails.back().first][tails.back().second] = true;
    }
  }

  present(map, "Tail 9 visited = ");
}

void Day9::solve()
{
  auto inst = extract();
  solveA(inst);
  solveB(inst);
}
