#include "Days/Day15.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
#include <unordered_map>

namespace
{
std::vector<Day15::Range> getBlockedTiles(Day15::Data& data, int64_t searchRow)
{
  std::vector<Day15::Range> ranges;

  for (auto pair : data)
  {
    auto distanceX = std::abs(pair.first.x - pair.second.x);
    auto distanceY = std::abs(pair.first.y - pair.second.y);
    auto taxiDistance = distanceX + distanceY;

    if (((searchRow >= pair.first.y) && (searchRow < (pair.first.y + taxiDistance))) || 
       ((searchRow <= pair.first.y) && (searchRow > (pair.first.y - taxiDistance))))
    {
      auto distanceToSearchRow = std::abs(searchRow - pair.first.y);
      auto blockedToPlace = (taxiDistance - distanceToSearchRow) * 2 + 1;
      ranges.push_back({ pair.first.x - blockedToPlace / 2, pair.first.x + blockedToPlace / 2 });
    }
  }

  return ranges;
}

void extractValues(std::vector<Day15::Range>& ret)
{

  // Combine ranges
  for (size_t k = 0; k < ret.size(); ++k)
  {
    for (size_t i = 0; i < ret.size(); ++i)
    {
      for (size_t j = i + 1; j < ret.size(); ++j)
      {
        if (ret[i].from <= ret[j].to && ret[i].from > ret[j].from)
        {
          ret[i].from = ret[j].from;
        }
        if (ret[i].to < ret[j].to && ret[i].to >= ret[j].from)
        {
          ret[i].to = ret[j].to;
        }
      }
    }
  }

  std::set<size_t> discard;
  // Remove already contained
  for (size_t i = 0; i < ret.size(); ++i)
  {
    for (size_t j = i + 1; j < ret.size(); ++j)
    {
      if (ret[i].from <= ret[j].from && ret[i].to >= ret[j].to)
      {
        discard.insert(j);
      }
    }
  }

  // Now remove them
  int index{};
  for (std::vector<Day15::Range>::iterator it = ret.begin(); it != ret.end();)
  {
    if (discard.find(index) != discard.end())
    {
      it = ret.erase(it);
    }
    else
    {
      it++;
    }
    index++;
  }
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
  extractValues(ret);

  int adjustment = 0;
  std::unordered_map<int64_t, int64_t> store;

  for (auto pair : data)
  {
    auto beacon = pair.second;
    auto sensor = pair.first;
    if (beacon.y == searchRow)
    {
      if (store[beacon.y] == 0)
      {
        store[beacon.y]++;
        adjustment++;
      }
    }
    if (sensor.y == searchRow)
    {
      if (store[sensor.y] == 0)
      {
        store[sensor.y]++;
        adjustment++;
      }
    }
  }

  int64_t sum{};
  for (auto v : ret)
  {
    sum += v.to - v.from + 1;
  }

  std::cout << "Number of blocked tiles = " << sum - adjustment << '\n';
}

void Day15::solveB(Data& data)
{
  //static constexpr int maxSize = 20;
  static constexpr int maxSize = 4000000;

  static constexpr int logInterval = 100000;
  static constexpr int logCalculationSize = 40000;

  int64_t closest = 0;

  for (int64_t i = 0; i <= maxSize; i++)
  {
    if ((i % logInterval) == 0)
    {
      std::cout << "Progress: " << i/ logCalculationSize << "%" << '\n';
    }
    auto ret = getBlockedTiles(data, i);

    // Constrain to [0, 4000000]
    for (auto& v : ret)
    {
      v.from = (v.from < 0) ? 0 : v.from;
      v.to = (v.to > maxSize) ? maxSize : v.to;
    }

    extractValues(ret);

    int64_t sum{};
    for (auto v : ret)
    {
      sum += v.to - v.from + 1;
    }

    if (sum < maxSize + 1 && sum > closest)
    {
      closest = sum;
    }

    if (sum == maxSize)
    {
      int64_t column = 0;
      for (auto v : ret)
      {
        bool run = true;
        for (int64_t value = v.from; value <= v.to; value++)
        {
          if (column != value)
          {
            run = false;
            break;
          }
          column++;
        }
        if (!run)
        {
          break;
        }
      }
      std::cout << "Distress beacon tuning frequency is = " << column * maxSize + i << '\n';
      break;
    }
  }
}

void Day15::solve()
{
  auto input = extract();
  solveA(input);
  solveB(input);
}
