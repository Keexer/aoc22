#pragma once

#include <queue>
#include <functional>
#include <stdint.h>

struct Monkey
{
  std::queue<uint64_t> items{};
  std::function<void(uint64_t&)> operation;
  int dividable{};
  int trueCondMonkey{};
  int falseCondMonkey{};
  int counted{};
};

class Day11
{
public:
  std::vector<Monkey> extract();
  void solveA(std::vector<Monkey> monkeys);
  void solveB(std::vector<Monkey> monkeys);
  void solve();
};