#include "Days/Day17.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

Day17::Input Day17::extract()
{
  std::ifstream file{ "../../Input/Input17.txt" };

  if (!file.is_open())
  {
    return {};
  }

  std::string line;

  std::getline(file, line);

  return line;
}

void Day17::solveA(Input& input)
{
  init();
  std::string inputTemp = input;
  std::vector<IShape*> shapeTemp = shapes;
  bool init = true;
  Rock* rock{};
  
  for (int i = 0; i < 2022;)
  {
    if (inputTemp.size() == 0)
    {
      inputTemp = input;
    }

    if (shapeTemp.size() == 0)
    {
      shapeTemp = shapes;
    }


    if (init)
    {
      init = false;
      IShape* shape = shapeTemp.front();
      shapeTemp.erase(shapeTemp.begin());

      size_t toAdd = shape->getShape().size();
      size_t emptyRows{};
      for (int i = static_cast<int>(map.size()) - 1; i >= 0; --i)
      {
        if (std::find(map[i].begin(), map[i].end(), true) != map[i].end())
        {
          break;
        }
        emptyRows++;
      }

      if (emptyRows < 3)
      {
        map.insert(map.end(), 3 - emptyRows, row);
      }

      if (emptyRows < 3 + toAdd)
      {
        map.insert(map.end(), toAdd + 3 - emptyRows, row);
      }
      else
      {
        map.resize(map.size() - (emptyRows - 3 - toAdd));
      }

      rock = new Rock(shape);
      rock->setStart(map.size() - toAdd);
    }

    char pushDirection = inputTemp.at(0);
    inputTemp.erase(0, 1);

    if (pushDirection == '<')
    {
      rock->moveLeft(map);
    }
    if (pushDirection == '>')
    {
      rock->moveRight(map);
    }

    if (rock->isLanded(map))
    {
      i++;
      rock->saveToMap(map);
      init = true;
      delete rock;
    }
    else
    {
      rock->moveDown();
    }
  }

  size_t sum{};

  for (int i = static_cast<int>(map.size()) - 1; i > 0; i--)
  {
    if (std::find(map[i].begin(), map[i].end(), true) != map[i].end())
    {
      sum = i;
      break;
    }
  }

  std::cout << "Map size: " << sum << '\n';
}

void Day17::solveB(Input&)
{
}

void Day17::solve()
{
  auto input = extract();
  solveA(input);
  solveB(input);
}
