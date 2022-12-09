#include "Days/Day9.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

namespace
{
  using Pos = std::pair<int, int>;
  void traverseMap(std::pair<char, uint8_t>& in, Pos& head, Pos& tail)
  {
    static constexpr double epsilon{ 1e-10 };

    if (in.first == 'U')
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
    else if (in.first == 'D')
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
    else if (in.first == 'L')
    {
      auto val = std::sqrt(std::pow((head.first - tail.first), 2) + std::pow((head.second - tail.second), 2));
      if (val > std::sqrt(2) + epsilon)
      {
        if (head.second != tail.second)
        {
          tail.second += (head.second > tail.second) ? 1 : -1 ;
        }
        if (head.first != tail.first)
        {
          tail.first += (head.first > tail.first) ? 1 : -1;
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
}

Day9::Instructions Day9::extract()
{
  std::ifstream file("../../Input/Input9.txt");

  if (!file.is_open())
  {
    return {};
  }

  std::string line;
  char operation;
  uint8_t steps;
  Instructions instructions;

  size_t counter{};

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
  std::vector<bool> row(10000, false);
  std::vector<std::vector<bool> > map(10000, row);

  static constexpr int initial{ 5000 };

  std::pair<int, int> head{ initial, initial };
  std::pair<int, int> tail{ head };
  map[initial][initial] = true;

  for (auto in : inst)
  {
    for (uint8_t i = 0; i < in.second; ++i)
    {
      if (in.first == 'U')
        --head.first;
      else if (in.first == 'D')
        ++head.first;
      else if (in.first == 'L')
        --head.second;
      else
        ++head.second;

      traverseMap(in, head, tail);
      map[tail.first][tail.second] = true;
    }
  }

  size_t visited{};

  for (auto mapRow : map)
  {
    visited += std::count(mapRow.begin(), mapRow.end(), true);
  }

  std::cout << "Tail visited = " << visited << '\n';
}

void Day9::solveB(Instructions& inst)
{
  // For simplicity create a large map to traverse
  std::vector<bool> row(10000, false);
  std::vector<std::vector<bool> > map(10000, row);

  static constexpr int initial{ 5000 };

  std::pair<int, int> head{ initial, initial };
  std::vector<std::pair<int, int> > tails{ 10, head }; // 0:th element is head
  map[initial][initial] = true;

  for (auto in : inst)
  {
    for (uint8_t i = 0; i < in.second; ++i)
    {
      if (in.first == 'U')
        --tails.front().first;
      else if (in.first == 'D')
        ++tails.front().first;
      else if (in.first == 'L')
        --tails.front().second;
      else
        ++tails.front().second;

      for (size_t i = 1; i < tails.size(); ++i)
      {
        traverseMap(in, tails[i-1], tails[i]);
      }
      map[tails.back().first][tails.back().second] = true;
    }
  }

  size_t visited{};

  for (auto mapRow : map)
  {
    visited += std::count(mapRow.begin(), mapRow.end(), true);
  }

  std::cout << "Tail 9 visited = " << visited << '\n';
}

void Day9::solve()
{
  auto inst = extract();
  solveA(inst);
  solveB(inst);
}
