#include "Days/Day17.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <memory>

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
  std::unique_ptr<Rock> rock{};
  static constexpr int loopCount = 2022;
  
  for (int i = 0; i < loopCount;)
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

      if (emptyRows < 3 + toAdd)
      {
        map.insert(map.end(), toAdd + 3 - emptyRows, row);
      }
      else
      {
        map.resize(map.size() - (emptyRows - 3 - toAdd));
      }

      rock = std::make_unique<Rock>(shape);
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

void Day17::solveB(Input& input)
{
  init();
  std::string inputTemp = input;
  std::vector<IShape*> shapeTemp = shapes;
  bool init = true;
  std::unique_ptr<Rock> rock{};
  std::vector<std::vector<bool> > pattern;
  static constexpr size_t eval = 10000;
  size_t rowUntilPatternRepeats{};
  bool findNumberOfRocksInPattern{ false };
  size_t startNumberOfFallingRocks{};
  size_t endNumberOfFallingRocks{};
  size_t rocksToAddAtEnd{};
  size_t startEnd{};
  size_t startEndSize{};
  bool findingLastRocks{ false };

  size_t result{};
  static constexpr size_t loopCount = 1'000'000'000'000;

  for (size_t i = 0; i < loopCount;)
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
      // Calculate on how many rows needed until pattern repeats itself
      if (i == eval * 2)
      {
        for (size_t k = 1; k < eval; k++)
        {
          pattern.push_back(map[eval + k]);

          if (!std::equal(pattern.back().begin(), pattern.back().end(), (map.begin() + eval)->begin()))
          {
            pattern.clear();
          }
          else
          {
            bool found = true;
            static constexpr int conditionUntilFound = 100;
            for (int j = 1; j < conditionUntilFound && found; j++)
            {
              found = std::equal(map[eval + k + j].begin(), map[eval + k + j].end(), (map.begin() + eval + j)->begin());
            }

            if (found)
            {
              rowUntilPatternRepeats = k;
              findNumberOfRocksInPattern = true;
              break;
            }
          }
        }
      }

      // Calculate how many rocks are stored in the found pattern
      if (findNumberOfRocksInPattern)
      {
        if (map.size() % rowUntilPatternRepeats < 3)
        {
          if (startNumberOfFallingRocks != 0)
          {
            endNumberOfFallingRocks = i;
            rocksToAddAtEnd = loopCount % (endNumberOfFallingRocks - startNumberOfFallingRocks);
            startEnd = i;
            inputTemp = input;
            shapeTemp = shapes;
            for (int e = static_cast<int>(map.size()) - 1; e >= 0; --e)
            {
              if (std::find(map[e].begin(), map[e].end(), true) != map[e].end())
              {
                startEndSize = e;
                break;
              }
            }
            findNumberOfRocksInPattern = false;
            findingLastRocks = true;
          }
          if (startNumberOfFallingRocks == 0)
          {
            startNumberOfFallingRocks = i;
            for (int e = static_cast<int>(map.size()) - 1; e >= 0; --e)
            {
              if (std::find(map[e].begin(), map[e].end(), true) != map[e].end())
              {
                break;
              }
            }
          }
        }
      }

      // Get the last rocks needed after pattern to drop
      if (findingLastRocks && i == startEnd + rocksToAddAtEnd)
      {
        size_t toAddAtEnd{};
        for (int e = static_cast<int>(map.size()) - 1; e >= 0; --e)
        {
          if (std::find(map[e].begin(), map[e].end(), true) != map[e].end())
          {
            toAddAtEnd = e - startEndSize;
            result = (loopCount / (endNumberOfFallingRocks - startNumberOfFallingRocks)) * rowUntilPatternRepeats + toAddAtEnd;
            std::cout << "Map size: " << result << '\n';
            return;
          }
        }
      }

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

      rock = std::make_unique<Rock>(shape);
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
    }
    else
    {
      rock->moveDown();
    }
  }
}

void Day17::solve()
{
  auto input = extract();
  solveA(input);
  solveB(input);
}
