#include "Days/Day14.h"

#include <fstream>
#include <sstream>
#include <utility>
#include <iostream>
#include <algorithm>

namespace
{

std::vector<std::string> seperateLine(std::string& line)
{
  std::vector<std::string> ret;
  while (line.find(" -> ") != std::string::npos)
  {
    std::string sub = line.substr(0, line.find(" -> "));
    ret.push_back(sub);
    line.erase(0, line.find(" -> ") + 4);
  }

  ret.push_back(line);

  return ret;
}

std::vector<Day14::Coordinates> getRocksPath(std::string& line)
{
  auto seperated = seperateLine(line);
  std::vector<Day14::Coordinates> ret;

  for (auto v : seperated)
  {
    Day14::Coordinates coordinates{};
    coordinates.x = std::stoi(v.substr(0, v.find(',')));
    v = v.erase(0, v.find(',') + 1);
    coordinates.y = std::stoi(v);

    ret.push_back(coordinates);
  }

  return ret;
}

void buildMap(Day14::Map& map, Day14::Input& input)
{
  for (auto rockPath : input)
  {
    for (size_t i = 0; i < rockPath.size() - 1; ++i)
    {
      int originX = rockPath[i].x;
      int originY = rockPath[i].y;
      int endX = rockPath[i + 1].x;
      int endY = rockPath[i + 1].y;

      if (originX == endX)
      {
        int smallest = (originY < endY) ? originY : endY;
        int largest = (originY > endY) ? originY : endY;
        for (int yPath = smallest; yPath <= largest; ++yPath)
        {
          map[yPath][originX] = Day14::STONE;
        }
      }
      else
      {
        int smallest = (originX < endX) ? originX : endX;
        int largest = (originX > endX) ? originX : endX;
        for (int xPath = smallest; xPath <= largest; ++xPath)
        {
          map[originY][xPath] = Day14::STONE;
        }
      }
    }
  }
}

void buildFloor(Day14::Map& map, Day14::Input& input)
{
  int maxY{};

  for (auto v : input)
  {
    int m = (*std::max_element(v.begin(), v.end(), [](const auto& a, const auto& b)
      {
        return a.y < b.y;
      })).y;
    maxY = (m > maxY) ? m : maxY;
  }

  for (size_t i = 0; i < map.front().size(); i++)
  {
    map[maxY + 2][i] = Day14::STONE;
  }
}

//char convertDebug(Day14::Point point)
//{
//  switch (point)
//  {
//  case Day14::FREE:
//    return '.';
//    break;
//  case Day14::STONE:
//    return '#';
//    break;
//  case Day14::SAND:
//    return 'O';
//    break;
//  }
//
//  return '@';
//}
//
//void debugPrintEx(std::vector<std::vector<Day14::Point> >& map)
//{
//  static constexpr int maxY = 12;
//  static constexpr int minX = 488;
//  static constexpr int maxX = 512;
//
//  for (int y = 0; y < maxY; ++y)
//  {
//    for (int x = minX; x < maxX; ++x)
//    {
//      std::cout << convertDebug(map[y][x]);
//    }
//    std::cout << '\n';
//  }
//}

bool spawnAndMoveOneSand(Day14::Map& map, int& result)
{
  static constexpr int sandOriginX = 500;
  static constexpr int sandOriginY = 0;

  Day14::Coordinates sand{sandOriginX, sandOriginY};
  bool isMoving = true;

  while (isMoving)
  {
    static constexpr int maxY = 499;
    static constexpr int maxX = 1001;

    // Check if sand reached endless void
    if (sand.y == maxY || ((sand.x == 1) || (sand.x == maxX)))
    {
      return false;
    }

    // Try move down
    if (map[sand.y + 1][sand.x] == Day14::FREE)
    {
      sand.y++;
    }
    // Try move down/left
    else if (map[sand.y + 1][sand.x - 1] == Day14::FREE)
    {
      sand.y++;
      sand.x--;
    }
    // Try move down/right
    else if (map[sand.y + 1][sand.x + 1] == Day14::FREE)
    {
      sand.y++;
      sand.x++;
    }
    // At rest
    else
    {
      if (map[sand.y][sand.x] == Day14::SAND)
      {
        return false;
      }

      map[sand.y][sand.x] = Day14::SAND;
      isMoving = false;
      ++result;
    }
  }

  return true;
}

}

Day14::Data Day14::extract()
{
  std::ifstream file{ "../../Input/Input14.txt" };

  if (!file.is_open())
  {
    return {};
  }

  std::string line;
  std::vector<std::vector<Coordinates> > input;

  while (std::getline(file, line))
  {
    input.push_back(getRocksPath(line));
  }

  static constexpr int maxY = 500;
  static constexpr int maxX = 1002;

  std::vector<std::vector<Point> > map{ maxY, std::vector<Point>{maxX, Point::FREE} };
  buildMap(map, input);

  //debugPrintEx(map);

  return { map, input };
}

void Day14::solveA(Data input)
{
  int result{};

  while (spawnAndMoveOneSand(input.first, result))
  {
    //debugPrintEx(input.first);
  }

  std::cout << "Total sand at rest = " << result << '\n';
}

void Day14::solveB(Data input)
{
  int result{};

  buildFloor(input.first, input.second);

  while (spawnAndMoveOneSand(input.first, result))
  {
    //debugPrintEx(input.first);
  }

  std::cout << "Total sand at reset with floor = " << result << '\n';
}

void Day14::solve()
{
  auto data = extract();
  solveA(data);
  solveB(data);
}
