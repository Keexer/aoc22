#pragma once

#include <queue>
#include <functional>

struct Monkey
{
  std::queue<unsigned int> items{};
  std::function<void(unsigned int&)> operation;
  int dividable{};
  int trueCondMonkey{};
  int falseCondMonkey{};
  int counted{};
  bool multiplication{ true };
};

class Day11
{
public:
  std::vector<Monkey> extract();
  void solveA(std::vector<Monkey> monkeys);
  void solveB(std::vector<Monkey> monkeys);
  void solve();
};