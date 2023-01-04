#include "Days/Day20.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>

namespace
{
  static constexpr int64_t FIRST_VALUE = 1000;
  static constexpr int64_t SECOND_VALUE = 2000;
  static constexpr int64_t THIRD_VALUE = 3000;
}

Day20::Data Day20::extract()
{
  Data ret;

  std::ifstream file{ "../../Input/Input20.txt" };

  if (!file.is_open())
  {
    return {};
  }

  std::string line{};
  int64_t val{};

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
  std::vector<int64_t> moveOrder(data.size());
  std::iota(moveOrder.begin(), moveOrder.end(), 0);

  for (size_t i = 0; i < data.size(); ++i)
  {
    auto it = std::find(moveOrder.begin(), moveOrder.end(), i);
    int64_t distance = static_cast<int64_t>(std::distance(moveOrder.begin(), it));
    int64_t steps = data.at(distance);
    moveValue(data, steps, distance);
    moveValue(moveOrder, steps, distance);
  }

  int64_t distanceToZero = static_cast<int64_t>(std::distance(data.begin(), std::find(data.begin(), data.end(), 0)));

  int64_t first = data.at((FIRST_VALUE + distanceToZero) % data.size());
  int64_t second = data.at((SECOND_VALUE + distanceToZero) % data.size());
  int64_t third = data.at((THIRD_VALUE + distanceToZero) % data.size());

  std::cout << "Sum of coordinates = " << first + second + third << '\n';
}

void Day20::solveB(Data data)
{
  static constexpr int64_t multiplicationNumber = 811589153;
  static constexpr int maxLoops = 10;

  std::transform(data.begin(), data.end(), data.begin(), std::bind(std::multiplies<int64_t>(), std::placeholders::_1, multiplicationNumber));
  std::vector<int64_t> moveOrder(data.size());
  std::iota(moveOrder.begin(), moveOrder.end(), 0);

  for (int mixingLoops = 0; mixingLoops < maxLoops; ++mixingLoops)
  {
    for (size_t i = 0; i < data.size(); ++i)
    {
      auto it = std::find(moveOrder.begin(), moveOrder.end(), i);
      int64_t distance = static_cast<int>(std::distance(moveOrder.begin(), it));
      int64_t steps = data.at(distance);
      moveValue(data, steps, distance);
      moveValue(moveOrder, steps, distance);
    }
  }

  int64_t distanceToZero = static_cast<int>(std::distance(data.begin(), std::find(data.begin(), data.end(), 0)));

  int64_t first = data.at((FIRST_VALUE + distanceToZero) % data.size());
  int64_t second = data.at((SECOND_VALUE + distanceToZero) % data.size());
  int64_t third = data.at((THIRD_VALUE + distanceToZero) % data.size());

  std::cout << "Sum of coordinates = " << first + second + third << '\n';
}

void Day20::solve()
{
  auto data = extract();
  solveA(data);
  solveB(data);
}

void Day20::moveValue(Data& transform, int64_t steps, int64_t currentPos)
{
  auto val = transform.at(currentPos);
  steps = steps % (static_cast<int64_t>(transform.size() - 1));
  if (steps == 0)
  {
    return;
  }
  if (steps < 0)
  {
    auto diff = currentPos + steps;
    if (diff == 0)
    {
      transform.erase(transform.begin() + currentPos);
      transform.insert(transform.end(), val);
    }
    else if (diff < 0)
    {
      transform.insert(transform.end() + diff, val);
      transform.erase(transform.begin() + currentPos);
    }
    else
    {
      transform.erase(transform.begin() + currentPos);
      transform.insert(transform.begin() + diff, val);
    }

    return;
  }
  
  // Go backwards
  if (steps + currentPos >= static_cast<int64_t>(transform.size()))
  {
    steps = steps + currentPos - (static_cast<int64_t>(transform.size()) - 1);
    transform.erase(transform.begin() + currentPos);
    transform.insert(transform.begin() + steps, val);
  }
  else
  {
    transform.erase(transform.begin() + currentPos);
    transform.insert(transform.begin() + currentPos + steps, val);
  }
}
