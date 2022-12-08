#include "Days/Day8.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

Day8::Matrix Day8::extract()
{
  std::ifstream file("../../Input/Input8.txt");

  if (!file.is_open())
  {
    return {};
  }

Matrix input{};
std::string line;

while (std::getline(file, line))
{
  input.emplace_back();
  for (auto c : line)
  {
    input.back().push_back(c - '0');
  }
}

return input;
}

void Day8::solveA(Matrix& input)
{
  std::vector<bool> temp(input.front().size(), false);
  std::vector<std::vector<bool> > visible(input.size(), temp);

  auto check = [&](size_t first, size_t second, int8_t& highest)
  {
    if (input[first][second] > highest)
    {
      visible[first][second] = true;
      highest = input[first][second];
    }
  };

  // Top
  for (size_t i = 1; i < input.front().size() - 1; ++i)
  {
    int8_t highest = -1;
    for (size_t j = 0; j < input.size() - 1; ++j)
    {
      check(j, i, highest);
    }
  }

  // Bottom
  for (size_t i = input.front().size() - 2; i > 0; --i)
  {
    int8_t highest = -1;
    for (size_t j = input.size() - 1; j > 0; --j)
    {
      check(j, i, highest);
    }
  }

  // Left
  for (size_t i = 1; i < input.size() - 1; ++i)
  {
    int8_t highest = -1;
    for (size_t j = 0; j < input.front().size() - 1; ++j)
    {
      check(i, j, highest);
    }
  }

  // Right
  for (size_t i = 1; i < input.size() - 1; ++i)
  {
    int8_t highest = -1;
    for (size_t j = input.front().size() - 1; j > 0; --j)
    {
      check(i, j, highest);
    }
  }

  ptrdiff_t numberOfVisible{};
  for (auto vec : visible)
  {
    numberOfVisible += std::count(vec.begin(), vec.end(), true);
  }

  static constexpr ptrdiff_t corners = 4;

  std::cout << "Number of visible trees = " << numberOfVisible + corners << '\n';
}

void Day8::solveB(Matrix& input)
{
  size_t maximum{};

  for (int i = 0; i < input.size(); ++i)
  {
    for (int j = 0; j < input.front().size(); ++j)
    {
      // For each element
      uint8_t origin = input[i][j];
      size_t topScore{};
      size_t bottomScore{};
      size_t rightScore{};
      size_t leftScore{};

      // Top
      for (int top = i - 1; top >= 0; --top)
      {
        ++topScore;
        if (input[top][j] >= origin)
        {
          break;
        }
      }

      // Bottom
      for (int bottom = i + 1; bottom < input.size(); ++bottom)
      {
        ++bottomScore;
        if (input[bottom][j] >= origin)
        {
          break;
        }
      }

      // Right
      for (int right = j + 1; right < input.front().size(); ++right)
      {
        ++rightScore;
        if (input[i][right] >= origin)
        {
          break;
        }
      }

      // Left
      for (int left = j - 1; left >= 0; --left)
      {
        ++leftScore;
        if (input[i][left] >= origin)
        {
          break;
        }
      }

      size_t sum = topScore * bottomScore * rightScore * leftScore;

      maximum = (sum > maximum) ? sum : maximum;
    }
  }

  std::cout << "Highest scenic score = " << maximum << '\n';
}

void Day8::solve()
{
  auto input = extract();
  solveA(input);
  solveB(input);
}
