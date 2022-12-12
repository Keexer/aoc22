#include "Days/Day10.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace
{
  static constexpr int MAX_CYCLES = 220;
  static constexpr int FIRST_CYCLE_EVAL = 20;
  static constexpr int PERIODIC_CYCLE_EVAL = 40;
}

Day10::Ops Day10::extract()
{
  std::ifstream file{"../../Input/Input10.txt"};
  
  if (!file.is_open())
  {
    return {};
  }

  std::string line;
  Ops op;

  while (std::getline(file, line))
  {
    if (line.find("noop") != std::string::npos)
    {
      op.emplace_back(std::make_unique<NOOP>());
    }
    else
    {
      op.emplace_back(std::make_unique<Add>(std::stoi(line.substr(line.find(" ") + 1))));
    }
  }

  return op;
}

void Day10::solveA(Ops& op)
{
  int v{1};
  int sum{};
  for (int i = 1; i <= MAX_CYCLES; ++i)
  {
    if (i % PERIODIC_CYCLE_EVAL == FIRST_CYCLE_EVAL)
    {
      int signalStrength = i * v;
      sum += signalStrength;
    }
    v += op.front()->run();
    if (op.front()->done())
    {
      op.pop_front();
    }
  }

  std::cout << "Sum of signal strenghts = " << sum << '\n';
}

void Day10::solveB(Ops& op)
{
  int v{ 1 };

  std::cout << "The capital letters!\n";
  static constexpr int maxRows = 6;
  static constexpr int pixelsPerRow = 40;

  for (int row = 0; row < maxRows; ++row)
  {
    for (int pixel = 0; pixel < pixelsPerRow; ++pixel)
    {
      if (pixel >= v - 1 && pixel <= v + 1)
      {
        std::cout << '#';
      }
      else
      {
        std::cout << '.';
      }
      v += op.front()->run();
      if (op.front()->done())
      {
        op.pop_front();
      }
    }
    std::cout << '\n';
  }
}

void Day10::solve()
{
  auto ops = extract();
  solveA(ops);
  auto ops2 = extract();
  solveB(ops2);
}
