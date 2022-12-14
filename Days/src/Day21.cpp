#include "Days/Day21.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <numeric>

Day21::Data Day21::extract()
{
  Data ret{};
  std::ifstream file{ "../../Input/Input21.txt" };

  if (!file.is_open())
  {
    return {};
  }

  std::string line{};

  while (std::getline(file, line))
  {
    Monkey m{};
    std::stringstream ss{line};
    std::string temp{};
    std::string monkeyName{};
    
    ss >> temp;
    temp.pop_back();
    monkeyName = temp;
    m.name = monkeyName;

    ss >> temp;
    if (temp.at(0) >= '0' && temp.at(0) <= '9')
    {
      m.value = std::stoi(temp);
      ret.insert({ monkeyName, m });
      continue;
    }

    m.monkey1 = temp;

    ss >> temp;
    if (temp.at(0) == '+')
    {
      m.op = Monkey::Operation::ADD;
    }
    else if (temp.at(0) == '-')
    {
      m.op = Monkey::Operation::SUBTRACT;
    }
    else if (temp.at(0) == '/')
    {
      m.op = Monkey::Operation::DIVIDE;
    }
    else
    {
      m.op = Monkey::Operation::MULTIPLY;
    }

    ss >> temp;
    m.monkey2 = temp;

    ret.insert({ monkeyName, m });
  }

  return ret;
}

void Day21::solveA(Data data)
{
  auto result = findYell(data, data.at("root"));
  std::cout << "Root will yell: " << result << '\n';
}

void Day21::solveB(Data data)
{
  static constexpr int64_t guessTimate = 20;
  int64_t min = std::numeric_limits<int64_t>::min();
  min = min >> guessTimate;
  int64_t max = std::numeric_limits<int64_t>::max();
  max = max >> guessTimate;
  auto initialVal = findEqual(data, data.at("root"));

  while (true)
  {
    int64_t toYell = (max - min) / 2 + min;
    data.at("humn").value = toYell;
    auto root = findEqual(data, data.at("root"));

    if (root.first == 0 && root.second == 0)
    {
      std::cout << "I Yell: " << toYell << '\n';
      break;
    }

    if (root.first < 0)
    {
      if (initialVal.first > 0)
      {
        max = toYell;
      }
      else
      {
        min = toYell;
      }
    }
    else
    {
      if (initialVal.first > 0)
      {
        min = toYell;
      }
      else
      {
        max = toYell;
      }
    }
  }
}

void Day21::solve()
{
  auto data = extract();
  solveA(data);
  solveB(data);
}

int64_t Day21::findYell(Data& data, Monkey monkey)
{
  if (data.at(monkey.name).value)
  {
    return *monkey.value;
  }
  
  int64_t val1 = findYell(data, data.at(monkey.monkey1));
  int64_t val2 = findYell(data, data.at(monkey.monkey2));

  switch (monkey.op)
  {
  case Monkey::Operation::ADD:
    return val1 + val2;
    break;
  case Monkey::Operation::SUBTRACT:
    return val1 - val2;
    break;
  case Monkey::Operation::MULTIPLY:
    return val1 * val2;
    break;
  case Monkey::Operation::DIVIDE:
    return val1 / val2;
    break;
  default:
    throw;
  }

  throw;
}

std::pair<int64_t, int64_t> Day21::findEqual(Data& data, Monkey monkey)
{
  if (data.at(monkey.name).value)
  {
    return { *monkey.value , 0};
  }

  auto val1 = findEqual(data, data.at(monkey.monkey1));
  auto val2 = findEqual(data, data.at(monkey.monkey2));

  if (monkey.name == "root")
  {
    return { val2.first - val1.first, val1.second + val2.second };
  }

  switch (monkey.op)
  {
  case Monkey::Operation::ADD:
    return { val1.first + val2.first, val1.second + val2.second };
    break;
  case Monkey::Operation::SUBTRACT:
    return { val1.first - val2.first, val1.second + val2.second };
    break;
  case Monkey::Operation::MULTIPLY:
    return { val1.first * val2.first, val1.second + val2.second };
    break;
  case Monkey::Operation::DIVIDE:
    return { val1.first / val2.first, val1.second + val2.second + val1.first % val2.first };
    break;
  default:
    throw;
  }

  throw;
}
