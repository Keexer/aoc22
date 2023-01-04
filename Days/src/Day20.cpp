#include "Days/Day20.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>

Day20::Data Day20::extract()
{
  Data ret;

  std::ifstream file{ "../../Input/Input20.txt" };

  if (!file.is_open())
  {
    return {};
  }

  std::string line;
  int val;

  while (std::getline(file, line))
  {
    std::stringstream s{ line };
    s >> val;
    ret.push_back(val);
  }

  return ret;
}

void Day20::solveA(Data data)
{
  std::vector<int> moveOrder(data.size());
  std::iota(moveOrder.begin(), moveOrder.end(), 0);

  for (int i = 0; i < data.size(); ++i)
  {
    auto it = std::find(moveOrder.begin(), moveOrder.end(), i);
    int distance = static_cast<int>(std::distance(moveOrder.begin(), it));
    int temp = data.at(distance);
    moveValue(data, temp, distance);
    moveValue(moveOrder, temp, distance);
  }

  int distanceToZero = static_cast<int>(std::distance(data.begin(), std::find(data.begin(), data.end(), 0)));

  int first = data.at((1000 + distanceToZero) % data.size());
  int second = data.at((2000 + distanceToZero) % data.size());
  int third = data.at((3000 + distanceToZero) % data.size());

  std::cout << "Sum of coordinates = " << first + second + third << '\n';
}

void Day20::solveB(Data data)
{
}

void Day20::solve()
{
  auto data = extract();
  solveA(data);
  solveB(data);
}

void Day20::moveValue(std::vector<int>& transform, int steps, int currentPos)
{
  if (steps == 0)
  {
    return;
  }
  else if (steps < 0)
  {
    while (steps < 0)
    {
      if (currentPos == 0)
      {
        transform.insert(transform.end() - 1, transform.front());
        transform.erase(transform.begin());
        currentPos = static_cast<int>(transform.size()) - 2;
      }
      else
      {
        std::iter_swap(transform.begin() + currentPos, transform.begin() + currentPos - 1);
        --currentPos;
      }
      ++steps;
    }
  }
  else if (steps > 0)
  {
    while (steps > 0)
    {
      if (currentPos == transform.size() - 1)
      {
        transform.insert(transform.begin() + 1, transform.back());
        transform.erase(transform.end() - 1);
        currentPos = 1;
      }
      else
      {
        std::iter_swap(transform.begin() + currentPos, transform.begin() + currentPos + 1);
        ++currentPos;
      }
      --steps;
    }
  }
}
