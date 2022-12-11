#include "Days/Day11.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Monkey> Day11::extract()
{
  std::ifstream file{ "../../Input/Input11.txt" };

  if (!file.is_open())
  {
    return {};
  }

  std::string line;

  std::vector<Monkey> monkeys;

  while (std::getline(file, line))
  {
    Monkey monkey;
    if (line.find("Monkey") != std::string::npos)
    {
      // Starting items
      std::string items;
      std::getline(file, items);
      items = items.substr(items.find(":") + 2);
      while (items.size() > 0)
      {
        monkey.items.push(std::stoi(items.substr(0, items.find(","))));
        if (items.find(",") != std::string::npos)
        {
          items = items.substr(items.find(",") + 2);
        }
        else
        {
          items = "";
        }
      }

      // Operation
      std::string operation;
      std::getline(file, operation);
      operation = operation.substr(operation.find("old") + 4);
      char arithmeticOp = operation.at(0);
      if (arithmeticOp == '+')
      {
        monkey.multiplication = false;
      }
      int modifier{};
      if (operation.find("old") == std::string::npos)
      {
        modifier = std::stoi(operation.substr(2));
      }
      monkey.operation = [modifier, arithmeticOp](unsigned int& old)
      {
        int temp = modifier;
        if (modifier == 0)
        {
          temp = old;
        }

        if (arithmeticOp == '*')
        {
          old *= temp;
        }
        else
        {
          old += temp;
        }
      };

      // Test
      std::string test;
      std::getline(file, test);
      monkey.dividable = std::stoi(test.substr(test.find("by") + 3));

      // True monkey
      std::string trueMonkey;
      std::getline(file, trueMonkey);
      monkey.trueCondMonkey = std::stoi(trueMonkey.substr(trueMonkey.find("monkey") + 7));

      // False monkey

      std::string falseMonkey;
      std::getline(file, falseMonkey);
      monkey.falseCondMonkey = std::stoi(falseMonkey.substr(falseMonkey.find("monkey") + 7));

      monkeys.push_back(monkey);
    }
  }

  return monkeys;
}

void Day11::solveA(std::vector<Monkey> monkeys)
{
  for (int i = 0; i < 20; ++i)
  {
    for (auto& monkey : monkeys)
    {
      while (!monkey.items.empty())
      {
        ++monkey.counted;
        auto item = monkey.items.front();
        monkey.items.pop();
        monkey.operation(item);
        item /= 3;
        
        if (item % monkey.dividable == 0)
        {
          monkeys.at(monkey.trueCondMonkey).items.push(item);
        }
        else
        {
          monkeys.at(monkey.falseCondMonkey).items.push(item);
        }
      }
    }
  }

  std::sort(monkeys.begin(), monkeys.end(), [](auto const& a, auto const& b) {return a.counted > b.counted; });

  std::cout << "Monkey business after 20 rounds = " << monkeys.at(0).counted * monkeys.at(1).counted << '\n';
}

void Day11::solveB(std::vector<Monkey> monkeys)
{
  for (int i = 0; i < 10000; ++i)
  {
    for (auto& monkey : monkeys)
    {
      while (!monkey.items.empty())
      {
        ++monkey.counted;
        auto item = monkey.items.front();
        monkey.items.pop();
        monkey.operation(item);
        item = item % monkey.dividable;

        if (item == 0)
        {
          monkeys.at(monkey.trueCondMonkey).items.push(item);
        }
        else
        {
          monkeys.at(monkey.falseCondMonkey).items.push(item);
        }
      }
    }
  }

  std::sort(monkeys.begin(), monkeys.end(), [](auto const& a, auto const& b) {return a.counted > b.counted; });

  int64_t result = static_cast<int64_t>(monkeys.at(0).counted) * static_cast<int64_t>(monkeys.at(1).counted);

  std::cout << "Monkey business after 10000 rounds = " << result << '\n';
}

void Day11::solve()
{
  auto monkeys = extract();
  solveA(monkeys);
  solveB(monkeys);
}
