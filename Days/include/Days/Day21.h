#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <cstdint>

class Day21
{
public:
  struct Monkey
  {
    enum class Operation
    {
      UNDEFINED = 0,
      ADD,
      SUBTRACT,
      MULTIPLY,
      DIVIDE
    };

    std::optional<int64_t> value{};
    std::string name{};
    std::string monkey1{};
    std::string monkey2{};
    Operation op{};
  };

  using Data = std::unordered_map<std::string, Monkey>;
  Data extract();
  void solveA(Data& data);
  void solveB(Data& data);
  void solve();

private:
  int64_t findYell(Data& data, Monkey monkey);
};