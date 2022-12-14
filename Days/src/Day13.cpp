#include "Days/Day13.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <optional>
#include <algorithm>

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
          static constexpr int ten = 10;
          order.back().data.push_back(ten);
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

  for (size_t i = 0; i < left.data.size(); ++i)
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
    if (line.size() > 1) // Notepad++ gives me Windows CR and NL, fix for linux. Fix input format later.... 
    {
      index++;
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

  for (size_t i = 0; i < packets.first.size(); ++i)
  {
    index++;
    //std::cout << "Traverse: " << index << '\n';
    auto r = compare(packets.first[i], packets.second[i]);
    if (r)
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
  Pack divier1Type = getEvaluationOrder("[[2]]");
  Pack divier2Type = getEvaluationOrder("[[6]]");

  std::vector<Pack> all;
  all.insert(all.begin(), packets.first.begin(), packets.first.end());
  all.insert(all.end(), packets.second.begin(), packets.second.end());
  all.push_back(divier1Type);
  all.push_back(divier2Type);

  std::sort(all.begin(), all.end(), [](auto const& a, auto const& b)
    {
      return *compare(a, b);
    });

  auto it1 = std::find_if(all.begin(), all.end(), [divier1Type](auto& a)
    {
      if (auto r = compare(divier1Type, a))
      {
        return *r;
      }
      return false;
    });
  auto it2 = std::find_if(all.begin(), all.end(), [divier2Type](auto& a)
    {
      if (auto r = compare(divier2Type, a))
      {
        return *r;
      }
  return false;
    });

  auto divider1 = std::distance(all.begin(), it1);
  auto divider2 = std::distance(all.begin(), it2);

  std::cout << "Decoder key = " << divider1 * divider2 << '\n';
}

void Day13::solve()
{
  auto data = extract();
  solveA(data);
  solveB(data);
}
