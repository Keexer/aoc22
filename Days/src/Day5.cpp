#include "Days/Day5.h"

#include <fstream>
#include <sstream>
#include <array>
#include <iostream>
#include <algorithm>

namespace
{
  static constexpr size_t NUM_STACKS = 9;
}

Day5::Return Day5::extract()
{
  std::ifstream file;
  file.open("../../Input/Input5.txt");

  if (!file.is_open())
  {
    return {};
  }

  std::array<std::vector<char>, NUM_STACKS> crateLine;
  std::string line;
  while (std::getline(file, line)) // parse crate init
  {
    if (line.size() == 0 || line[0] == '\r')
    {
      break;
    }

    for (size_t i = 1; i < line.size(); i += 4)
    {
      if (line[i] >= 'A' && line[i] <= 'Z')
      {
        crateLine.at(i / 4).push_back(line[i]);
      }
    }
  }

  CrateStack crateStack;

  for (size_t i = 0; i < crateLine.size(); ++i)
  {
    std::reverse(crateLine.at(i).begin(), crateLine.at(i).end());
    std::stack<char> stack;
    for (auto v : crateLine.at(i))
    {
      stack.push(v);;
    }
    crateStack.crateStack.push_back(stack);
  }

  Return ret;
  ret.stack = crateStack;

  while (std::getline(file, line)) // parse instructions
  {
    Instructions inst{};

    std::istringstream ss(line);
    for (std::string s; ss >> s; )
    {
      if (s == "move")
      {
        ss >> s;
        inst.move = std::stoi(s);
      }
      if (s == "from")
      {
        ss >> s;
        inst.from = std::stoi(s) - 1;
      }
      if (s == "to")
      {
        ss >> s;
        inst.to = std::stoi(s) - 1;
      }
    }
    ret.instructions.push_back(inst);
  }

  return ret;
}

void Day5::solveA(Return ret)
{
  for (auto v : ret.instructions)
  {
    auto& to = ret.stack.crateStack[v.to];
    auto& from = ret.stack.crateStack[v.from];
    for (int i = 0; i < v.move; ++i)
    {
      to.push(from.top());
      from.pop();
    }
  }

  std::cout << "Top crate 9000: ";

  for (auto result : ret.stack.crateStack)
  {
    std::cout << result.top();
  }

  std::cout << '\n';
}

void Day5::solveB(Return ret)
{
  std::stack<char> temp;

  for (auto v : ret.instructions)
  {
    auto& to = ret.stack.crateStack[v.to];
    auto& from = ret.stack.crateStack[v.from];
    for (int i = 0; i < v.move; ++i)
    {
      temp.push(from.top());
      from.pop();
    }
    for (int i = 0; i < v.move; ++i)
    {
      to.push(temp.top());
      temp.pop();
    }
  }

  std::cout << "Top crate 9001: ";

  for (auto result : ret.stack.crateStack)
  {
    std::cout << result.top();
  }

  std::cout << '\n';
}

void Day5::solve()
{
  auto ret = extract();
  solveA(ret);
  solveB(ret);
}
