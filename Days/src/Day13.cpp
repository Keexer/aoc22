#include "Days/Day13.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <optional>
#include <cassert>

namespace
{
Day13::Pack getEvaluationOrder(std::string line)
{
  using Pack = Day13::Pack;
  Pack ret;
  std::vector<Pack> order;
  int openBrackets{};
  int peek{};
  bool skip{ false };

  for (auto c : line)
  {
    peek++;
    if (skip)
    {
      skip = false;
      continue;
    }

    if (c == '[')
    {
      openBrackets++;
      order.push_back(Pack{});
    }
    else if (c == ']')
    {
      openBrackets--;
      if (openBrackets == 0)
      {
        assert(order.size() == 1);
        ret = order.front();
      }
      else
      {
        auto temp = order.end() - 2;
        temp->data.push_back(order.back());
        order.pop_back();
      }
    }
    else if (c >= '0' && c <= '9')
    {
      if (c == '1')
      {
        if (line.at(peek) == '0')
        {
          order.back().data.push_back(10);
          skip = true;
        }
        else
        {
          order.back().data.push_back(1);
        }
      }
      else
      {
        order.back().data.push_back(c - '0');
      }
    }
    else
    {
      // Nothing
    }
  }

  return ret;
}

std::optional<bool> compare(Day13::Pack left, Day13::Pack right)
{
  using Pack = Day13::Pack;
  std::optional<bool> ret;

  for (int i = 0; i < left.data.size(); ++i)
  {
    if (right.data.size() <= i)
    {
      ret = false;
    }
    else if (std::holds_alternative<int>(left.data[i]) && std::holds_alternative<int>(right.data[i]))
    {
      auto leftVal = std::get<int>(left.data[i]);
      auto rightVal = std::get<int>(right.data[i]);
      if (leftVal < rightVal)
      {
        ret = true;
      }
      if (leftVal > rightVal)
      {
        ret = false;
      }
    }
    else if (std::holds_alternative<Pack>(left.data[i]) && std::holds_alternative<Pack>(right.data[i]))
    {
      ret = compare(std::get<Pack>(left.data[i]), std::get<Pack>(right.data[i]));
    }
    else if (std::holds_alternative<Pack>(left.data[i]) && std::holds_alternative<int>(right.data[i]))
    {
      Pack p;
      p.data.push_back(right.data[i]);
      ret = compare(std::get<Pack>(left.data[i]), Pack{ p });
    }
    else if (std::holds_alternative<int>(left.data[i]) && std::holds_alternative<Pack>(right.data[i]))
    {
      Pack p;
      p.data.push_back(left.data[i]);
      ret = compare(Pack{ p }, std::get<Pack>(right.data[i]));
    }

    if (!ret && (i == left.data.size() - 1) && (i < right.data.size() - 1))
    {
      ret = true;
    }

    if (ret)
    {
      return ret;
    }
  }

  if (left.data.size() < right.data.size())
  {
    ret = true;
  }

  return ret;
}

}

Day13::Data Day13::extract()
{
  std::ifstream file{ "../../Input/Input13.txt" };

  if (!file.is_open())
  {
    return {};
  }

  std::string line;
  std::vector<Pack> packetsLeft;
  std::vector<Pack> packetsRight;
  size_t index{ 0 };

  while (std::getline(file, line))
  {
    if (line.size() > 0)
    {
      index++;
      if (index == 25)
      {
        int t = 0;
      }
      if (index % 2 == 0)
      { 
        packetsRight.push_back(getEvaluationOrder(line));
      }
      else
      {
        packetsLeft.push_back(getEvaluationOrder(line));
      }
    }
  }

  return {packetsLeft, packetsRight};
}

void Day13::solveA(Data& packets)
{
  int sum{};
  int index{};
  for (int i = 0; i < packets.first.size(); ++i)
  {
    index++;
    if (auto r = compare(packets.first[i], packets.second[i]); r)
    {
      if (*r)
      {
        sum += index;
      }
    }
  }

  std::cout << "Sum of right order indices = " << sum << '\n';
}

void Day13::solveB(Data& packets)
{
}

void Day13::solve()
{
  auto data = extract();
  solveA(data);
  solveB(data);
}
