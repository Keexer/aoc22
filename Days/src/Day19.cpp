#include "Days/Day19.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>

Day19::Data Day19::extract()
{
  Data ret;

  std::ifstream file{"../../Input/Input19.txt"};

  if (!file.is_open())
  {
    return {};
  }

  std::string line;

  while (std::getline(file, line))
  {
    Blueprint b;
    std::string skip;
    std::stringstream s{ line };

    s >> skip;
    s >> b.number;
    s >> skip >> skip >> skip >> skip >> skip;
    s >> b.oreRobot.oreCost;
    s >> skip >> skip >> skip >> skip >> skip;
    s >> b.clayRobot.oreCost;
    s >> skip >> skip >> skip >> skip >> skip;
    s >> b.obsidianRobot.oreCost;
    s >> skip >> skip;
    s >> b.obsidianRobot.clayCost;
    s >> skip >> skip >> skip >> skip >> skip;
    s >> b.geodeRobot.oreCost;
    s >> skip >> skip;
    s >> b.geodeRobot.obsidianCost;

    ret.push_back(b);
  }

  return ret;
}

void Day19::solveA(Data& blueprints)
{
  Geode max{};
  Geode geodes1{};
  Geode geodes2{};
  static constexpr int maxTime = 24;
  int index{};
  int result{};

  for (const auto& b : blueprints)
  {
    ++index;
    Material m{};
    Robots r{};
    geodes1 = dfs(b, m, r, 0, maxTime, true, false, false, false);
    geodes2 = dfs(b, m, r, 0, maxTime, false, true, false, false);

    max = std::max(geodes1, geodes2);
    result += index * max;
  }

  std::cout << "Quality level of blueprint = " << result << '\n';
}

void Day19::solveB(Data& blueprints)
{
  Geode max{};
  Geode geodes1{};
  Geode geodes2{};
  static constexpr int maxTime = 32;
  int index{};
  int result{};
  std::vector<Geode> geodes;

  for (const auto& b : blueprints)
  {
    if (index >= 3)
    {
      break;
    }
    ++index;
    Material m{};
    Robots r{};
    geodes1 = dfs(b, m, r, 0, maxTime, true, false, false, false);
    geodes2 = dfs(b, m, r, 0, maxTime, false, true, false, false);

    max = std::max(geodes1, geodes2);
    geodes.push_back(max);
  }

  result = std::accumulate(geodes.begin(), geodes.end(), 1, std::multiplies<int>());

  std::cout << "Total geodes collected = " << result << '\n';
}

void Day19::solve()
{
  auto data = extract();
  solveA(data);
  solveB(data);
}

int Day19::dfs(const Blueprint& blueprint, Material material, Robots robots, int time, int maxTime, bool createOreRobot, bool createClayRobot, bool createObsidianRobot, bool createGeodeRobot)
{
  int minutes = maxTime;
  if (time >= minutes)
  {
    return material.geode;
  }

  Geode max = material.geode + (minutes - time) * robots.geodeRobots;

  if (createOreRobot && robots.oreRobots == std::max({blueprint.oreRobot.oreCost, blueprint.clayRobot.oreCost, blueprint.obsidianRobot.oreCost, blueprint.geodeRobot.oreCost}))
  {
    createOreRobot = false;
  }
  if (createClayRobot && robots.clayRobots == blueprint.obsidianRobot.clayCost)
  {
    createClayRobot = false;
  }
  if (createObsidianRobot && robots.obsidianRobots == blueprint.geodeRobot.obsidianCost)
  {
    createObsidianRobot = false;
  }

  if (createOreRobot)
  {
    if (material.ore + robots.oreRobots * (minutes - time) < blueprint.oreRobot.oreCost)
    {
      return max;
    }

    while (material.ore < blueprint.oreRobot.oreCost)
    {
      waitCycle(material, robots, time, minutes);
    }

    material.ore -= blueprint.oreRobot.oreCost;
    waitCycle(material, robots, time, minutes);
    robots.oreRobots++;

    int value = dfs(blueprint, material, robots, time, maxTime, true, false, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, maxTime, false, true, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, maxTime, false, false, true, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, maxTime, false, false, false, true);
    if (value > max)
      max = value;
  }
  if (createClayRobot)
  {
    if (material.ore + robots.oreRobots * (minutes - time) < blueprint.clayRobot.oreCost)
    {
      return max;
    }

    while (material.ore < blueprint.clayRobot.oreCost)
    {
      waitCycle(material, robots, time, minutes);
    }

    material.ore -= blueprint.clayRobot.oreCost;
    waitCycle(material, robots, time, minutes);
    robots.clayRobots++;

    int value = dfs(blueprint, material, robots, time, maxTime, true, false, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, maxTime, false, true, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, maxTime, false, false, true, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, maxTime, false, false, false, true);
    if (value > max)
      max = value;
  }
  if (createObsidianRobot)
  {
    if ((material.ore + robots.oreRobots * (minutes - time) < blueprint.obsidianRobot.oreCost) || (material.clay + robots.clayRobots * (minutes - time) < blueprint.obsidianRobot.clayCost))
    {
      return max;
    }

    while ((material.ore < blueprint.obsidianRobot.oreCost) || (material.clay < blueprint.obsidianRobot.clayCost))
    {
      waitCycle(material, robots, time, minutes);
    }

    material.ore -= blueprint.obsidianRobot.oreCost;
    material.clay -= blueprint.obsidianRobot.clayCost;
    waitCycle(material, robots, time, minutes);
    robots.obsidianRobots++;

    int value = dfs(blueprint, material, robots, time, maxTime, true, false, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, maxTime, false, true, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, maxTime, false, false, true, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, maxTime, false, false, false, true);
    if (value > max)
      max = value;
  }
  if (createGeodeRobot)
  {
    if ((material.ore + robots.oreRobots * (minutes - time) < blueprint.geodeRobot.oreCost) || (material.obsidian + robots.obsidianRobots * (minutes - time) < blueprint.geodeRobot.obsidianCost))
    {
      return max;
    }

    while ((material.ore < blueprint.geodeRobot.oreCost) || (material.obsidian < blueprint.geodeRobot.obsidianCost))
    {
      waitCycle(material, robots, time, minutes);
    }

    material.ore -= blueprint.geodeRobot.oreCost;
    material.obsidian -= blueprint.geodeRobot.obsidianCost;
    waitCycle(material, robots, time, minutes);
    robots.geodeRobots++;

    int value = dfs(blueprint, material, robots, time, maxTime, true, false, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, maxTime, false, true, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, maxTime, false, false, true, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, maxTime, false, false, false, true);
    if (value > max)
      max = value;
  }

  return max;
}

void Day19::waitCycle(Material& material, Robots robots, int& time, int maxTime)
{
  if (time == maxTime)
  {
    return;
  }

  time++;

  material.ore += robots.oreRobots;
  material.clay += robots.clayRobots;
  material.obsidian += robots.obsidianRobots;
  material.geode += robots.geodeRobots;
}
