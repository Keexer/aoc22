#include "Days/Day18.h"

#include <fstream>
#include <sstream>
#include <iostream>

using NodeType = Day18::NodeType;
using Matrix3 = std::vector<std::vector<std::vector<NodeType> > >;

namespace
{

Matrix3 createSpace(Day18::Data& input)
{
  static constexpr int sizeOfCube = 22;
  std::vector<NodeType> temp(sizeOfCube, NodeType::AIR);
  std::vector<std::vector<NodeType> > temp2(sizeOfCube, temp);
  Matrix3 space(sizeOfCube, temp2);

  for (const auto& v : input)
  {
    space.at(v.x + 1).at(v.y + 1).at(v.z + 1) = NodeType::LAVA;
  }

  return space;
}

bool checkSide(const Matrix3& matrix, const int x, const int y, const int z, NodeType type)
{
  return matrix.at(x).at(y).at(z) == type;
}

int getOpenSides(const Matrix3& matrix, const int x, const int y, const int z, NodeType type)
{
  int sides{};

  sides += (checkSide(matrix, x + 1, y, z, type)) ? 1 : 0;
  sides += (checkSide(matrix, x - 1, y, z, type)) ? 1 : 0;
  sides += (checkSide(matrix, x, y + 1, z, type)) ? 1 : 0;
  sides += (checkSide(matrix, x, y - 1, z, type)) ? 1 : 0;
  sides += (checkSide(matrix, x, y, z + 1, type)) ? 1 : 0;
  sides += (checkSide(matrix, x, y, z - 1, type)) ? 1 : 0;

  return sides;
}

void fillWithWater(Matrix3& matrix, int x, int y, int z)
{
  if (matrix.at(x).at(y).at(z) == NodeType::LAVA || matrix.at(x).at(y).at(z) == NodeType::WATER)
  {
    return;
  }

  matrix.at(x).at(y).at(z) = NodeType::WATER;

  if (x + 1 < static_cast<int>(matrix.size()))
    fillWithWater(matrix, x + 1, y, z);
  if (x - 1 > 0)
    fillWithWater(matrix, x - 1, y, z);
  if (y + 1 < static_cast<int>(matrix.size()))
    fillWithWater(matrix, x, y + 1, z);
  if (y - 1 > 0)
    fillWithWater(matrix, x, y - 1, z);
  if (z + 1 < static_cast<int>(matrix.size()))
    fillWithWater(matrix, x, y, z + 1);
  if (z - 1 > 0)
    fillWithWater(matrix, x, y, z - 1);
}

}

Day18::Data Day18::extract()
{
  Data ret;

  std::ifstream file{"../../Input/Input18.txt"};

  if (!file.is_open())
  {
    return {};
  }

  std::string line;

  while (std::getline(file, line))
  {
    Cube c{};
    char comma{};
    std::stringstream s{line};
  
    s >> c.x;
    s >> comma;
    s >> c.y;
    s >> comma;
    s >> c.z;

    ret.push_back(c);
  }

  return ret;
}

void Day18::solveA(Data& input)
{
  int sum{};

  Matrix3 space = createSpace(input);

  for (int x = 0; x < static_cast<int>(space.size()); ++x)
  {
    for (int y = 0; y < static_cast<int>(space.size()); ++y)
    {
      for (int z = 0; z < static_cast<int>(space.size()); ++z)
      {
        if (space.at(x).at(y).at(z) == NodeType::LAVA)
        {
          sum += getOpenSides(space, x, y, z, NodeType::AIR);
        }
      }
    }
  }

  std::cout << "Sum of open sides: " << sum << '\n';
}

void Day18::solveB(Data& input)
{
  int sum{};
  
  Matrix3 space = createSpace(input);

  fillWithWater(space, 0, 0, 0);

  for (int x = 0; x < static_cast<int>(space.size()); ++x)
  {
    for (int y = 0; y < static_cast<int>(space.size()); ++y)
    {
      for (int z = 0; z < static_cast<int>(space.size()); ++z)
      {
        if (space.at(x).at(y).at(z) == NodeType::LAVA)
        {
          sum += getOpenSides(space, x, y, z, NodeType::WATER);
        }
      }
    }
  }

  std::cout << "Sum of sides with water: " << sum << '\n';
}

void Day18::solve()
{
  auto input = extract();
  solveA(input);
  solveB(input);
}
