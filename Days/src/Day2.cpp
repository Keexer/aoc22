#include "Days/Day2.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

static constexpr char ROCK = 'A';
static constexpr char PAPER = 'B';
static constexpr char SCISSOR = 'C';

int shapeScore(char shape)
{
  return shape - '@';
}

constexpr char getOpposite(char opponent)
{
  if (opponent == ROCK)
  {
    return PAPER;
  }
  if (opponent == PAPER)
  {
    return SCISSOR;
  }
  else
  {
    return ROCK;
  }
}

constexpr char getLosing(char opponent)
{
  if (opponent == ROCK)
  {
    return SCISSOR;
  }
  if (opponent == PAPER)
  {
    return ROCK;
  }
  else
  {
    return PAPER;
  }
}

Day2::Cont Day2::extract()
{
  Cont guide{};

  std::ifstream file;
  file.open("../../Input/Input2.txt");

  if (!file.is_open())
  {
    return {};
  }

  std::string line;
  while (std::getline(file, line))
  {
    guide.push_back({ line[0], line[2] });
  }

  return guide;
}

void Day2::solveA(Day2::Cont& cont)
{
  static constexpr int win = 6;
  static constexpr int draw = 3;

  Day2::Cont temp = cont;
  std::for_each(temp.begin(), temp.end(), [](auto& vec)
    {
      static constexpr int diff = 'W' - '@';
  vec.second -= diff;
    }
  );

  int score{};

  for (auto v : temp)
  {
    score += shapeScore(v.second);
    score += (v.first == v.second) ? draw : 0;
    score += (v.second == getOpposite(v.first)) ? win : 0;
  }

  std::cout << "First task: Total score = " << score << '\n';
}

void Day2::solveB(Day2::Cont& cont)
{
  static constexpr int win = 6;
  static constexpr int draw = 3;

  int score{};

  for (auto v : cont)
  {
    switch (v.second)
    {
    case 'X':
      score += shapeScore(getLosing(v.first));
      break;
    case 'Y':
      score += draw;
      score += shapeScore(v.first);
      break;
    case 'Z':
      score += win;
      score += shapeScore(getOpposite(v.first));
      break;
    }
  }

  std::cout << "Second task: New total score = " << score << '\n';
}

void Day2::solve()
{
  auto data = extract();
  solveA(data);
  solveB(data);
}
