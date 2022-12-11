#include "Days/Day10.h"

#include <fstream>
#include <iostream>
#include <sstream>

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
  for (int i = 1; i <= 220; ++i)
  {
    if (i % 40 == 20)
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

  for (int row = 0; row < 6; ++row)
  {
    for (int pixel = 0; pixel < 40; ++pixel)
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
