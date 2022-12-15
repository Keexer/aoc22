#include "Days/Day15.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <set>

namespace
{
std::set<int64_t> getBlockedTiles(Day15::Data& data, int searchRow)
{
  std::set<int64_t> blockOnSearchRow;

  for (auto pair : data)
  {
    auto distanceX = std::abs(pair.first.x - pair.second.x);
    auto distanceY = std::abs(pair.first.y - pair.second.y);
    auto taxiDistance = distanceX + distanceY;

    if ((searchRow >= pair.first.y) && (searchRow < (pair.first.y + taxiDistance)))
    {
      auto distanceToSearchRow = std::abs(searchRow - pair.first.y);
      auto blockedToPlace = (taxiDistance - distanceToSearchRow) * 2 + 1;
      blockOnSearchRow.insert(pair.first.x);
      for (int i = 1; i <= blockedToPlace / 2; i++)
      {
        blockOnSearchRow.insert(pair.first.x - i);
        blockOnSearchRow.insert(pair.first.x + i);
      }
    }
    else if ((searchRow <= pair.first.y) && (searchRow > (pair.first.y - taxiDistance))) // Can put in if above and make distanceToSearchRow std::abs();
    {
      auto distanceToSearchRow = pair.first.y - searchRow;
      auto blockedToPlace = (taxiDistance - distanceToSearchRow) * 2 + 1;
      blockOnSearchRow.insert(pair.first.x);
      for (int i = 1; i <= blockedToPlace / 2; i++)
      {
        blockOnSearchRow.insert(pair.first.x - i);
        blockOnSearchRow.insert(pair.first.x + i);
      }
    }
  }

  return blockOnSearchRow;
}

Day15::Coords findDistressBeacon(Day15::Data& data, int64_t maxSize)
{
  for (int64_t y = 0; y <= maxSize; y++)
  {
    std::set<int64_t> blockOnSearchRow;
 
    for (auto pair : data)
    {
      auto distanceX = std::abs(pair.first.x - pair.second.x);
      auto distanceY = std::abs(pair.first.y - pair.second.y);
      auto taxiDistance = distanceX + distanceY;

      if ((y >= pair.first.y) && (y < (pair.first.y + taxiDistance)))
      {
        auto distanceToSearchRow = std::abs(y - pair.first.y);
        auto blockedToPlace = (taxiDistance - distanceToSearchRow) * 2 + 1;
        if ((pair.first.x >= 0) && (pair.first.x <= maxSize))
        {
          blockOnSearchRow.insert(pair.first.x);
        }
        for (int i = 1; i <= blockedToPlace / 2; i++)
        {
          bool overflow1 = pair.first.x - i < 0;
          bool overflow2{ pair.first.x + i > maxSize };
          if (!overflow1)
          {
            blockOnSearchRow.insert(pair.first.x - i);
          }
          if (!overflow2)
          {
            blockOnSearchRow.insert(pair.first.x + i);
          }
          if (overflow1 && overflow2)
          {
            break;
          }
        }
      }
      else if ((y <= pair.first.y) && (y > (pair.first.y - taxiDistance))) // Can put in if above and make distanceToSearchRow std::abs();
      {
        auto distanceToSearchRow = pair.first.y - y;
        auto blockedToPlace = (taxiDistance - distanceToSearchRow) * 2 + 1;
        if ((pair.first.x >= 0) && (pair.first.x <= maxSize))
        {
          blockOnSearchRow.insert(pair.first.x);
        }
        for (int i = 1; i <= blockedToPlace / 2; i++)
        {
          bool overflow1 = pair.first.x - i < 0;
          bool overflow2{ pair.first.x + i > maxSize };
          if (!overflow1)
          {
            blockOnSearchRow.insert(pair.first.x - i);
          }
          if (!overflow2)
          {
            blockOnSearchRow.insert(pair.first.x + i);
          }
          if (overflow1 && overflow2)
          {
            break;
          }
        }
      }
    }

    if (blockOnSearchRow.size() > static_cast<size_t>(maxSize))
    {
      continue;
    }

    if (blockOnSearchRow.size() == maxSize)
    {
      int64_t foundX{ 0 };
      for (int64_t i = 0; i <= maxSize; i++)
      {
        if (!blockOnSearchRow.contains(i))
        {
          foundX = i;
          break;
        }
      }
      return {foundX, y};
    }
  }

  return { 0, 0 };
}
}

Day15::Data Day15::extract()
{
  std::ifstream file{ "../../Input/Input15.txt" };

  if (!file.is_open())
  {
    return {};
  }

  std::string line;
  std::vector<std::pair<Sensor, Beacon> > ret;

  while (std::getline(file, line))
  {
    std::pair<Sensor, Beacon> pair;

    std::string sensorStr = line.substr(0, line.find(":"));
    std::string beaconStr = line.substr(line.find(":"));
    
    pair.first.x = std::stoi(sensorStr.substr(sensorStr.find("x=") + 2, sensorStr.find(",") - sensorStr.find("x=") - 2));
    pair.first.y = std::stoi(sensorStr.substr(sensorStr.find("y=") + 2));

    pair.second.x = std::stoi(beaconStr.substr(beaconStr.find("x=") + 2, beaconStr.find(",") - beaconStr.find("x=") - 2));
    pair.second.y = std::stoi(beaconStr.substr(beaconStr.find("y=") + 2));

    ret.push_back(pair);
  }

  return ret;
}

void Day15::solveA(Data& data)
{
  //static constexpr int searchRow = 10;
  static constexpr int searchRow = 2000000;

  auto ret = getBlockedTiles(data, searchRow);

  for (auto pair : data)
  {
    auto beacon = pair.second;
    auto sensor = pair.first;
    if (beacon.y == searchRow)
    {
      if (ret.find(beacon.x) != ret.end())
      {
        ret.erase(beacon.x);
      }
    }
    if (sensor.y == searchRow)
    {
      if (ret.find(sensor.x) != ret.end())
      {
        ret.erase(sensor.x);
      }
    }
  }

  std::cout << "Number of blocked tiles = " << ret.size() << '\n';
}

void Day15::solveB(Data& data)
{
  //static constexpr int maxSize = 20;
  static constexpr int maxSize = 4000000;

  auto val = findDistressBeacon(data, maxSize);
  std::cout << "Distress beacon tuning frequency is = " << val.x * 4000000 + val.y << '\n';
}

void Day15::solve()
{
  auto input = extract();
  solveA(input);
  solveB(input);
}
