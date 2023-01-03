#include "Days/Day19.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

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
  int index{};
  int result{};

  for (const auto& b : blueprints)
  {
    ++index;
    Material m{};
    Robots r{};
    geodes1 = dfs(b, m, r, 0, true, false, false, false);
    geodes2 = dfs(b, m, r, 0, false, true, false, false);

    max = std::max(geodes1, geodes2);
    result += index * max;
  }

  std::cout << "Quality level of blueprint = " << result << '\n';
}

void Day19::solveB(Data&)
{
}

void Day19::solve()
{
  auto data = extract();
  solveA(data);
  solveB(data);
}

int Day19::dfs(const Blueprint& blueprint, Material material, Robots robots, int time, bool createOreRobot, bool createClayRobot, bool createObsidianRobot, bool createGeodeRobot)
{
  static constexpr int minutes = 24;
  if (time >= minutes)
  {
    return material.geode;
  }

  Geode max = material.geode + (minutes - time) * robots.geodeRobots;

  if (createOreRobot && robots.oreRobots == std::max({blueprint.oreRobot.oreCost, blueprint.clayRobot.oreCost, blueprint.obsidianRobot.oreCost, blueprint.geodeRobot.oreCost}))
  {
    return max;
  }
  if (createClayRobot && robots.clayRobots == blueprint.obsidianRobot.clayCost)
  {
    return max;
  }
  if (createObsidianRobot && robots.obsidianRobots == blueprint.geodeRobot.obsidianCost)
  {
    return max;
  }

  if (createOreRobot)
  {
    if (material.ore + robots.oreRobots * (minutes - time) < blueprint.oreRobot.oreCost)
    {
      return max;
    }

    while (material.ore < blueprint.oreRobot.oreCost)
    {
      waitCycle(material, robots, time);
    }

    material.ore -= blueprint.oreRobot.oreCost;
    waitCycle(material, robots, time);
    robots.oreRobots++;

    int value = dfs(blueprint, material, robots, time, true, false, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, false, true, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, false, false, true, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, false, false, false, true);
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
      waitCycle(material, robots, time);
    }

    material.ore -= blueprint.clayRobot.oreCost;
    waitCycle(material, robots, time);
    robots.clayRobots++;

    int value = dfs(blueprint, material, robots, time, true, false, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, false, true, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, false, false, true, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, false, false, false, true);
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
      waitCycle(material, robots, time);
    }

    material.ore -= blueprint.obsidianRobot.oreCost;
    material.clay -= blueprint.obsidianRobot.clayCost;
    waitCycle(material, robots, time);
    robots.obsidianRobots++;

    int value = dfs(blueprint, material, robots, time, true, false, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, false, true, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, false, false, true, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, false, false, false, true);
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
      waitCycle(material, robots, time);
    }

    material.ore -= blueprint.geodeRobot.oreCost;
    material.obsidian -= blueprint.geodeRobot.obsidianCost;
    waitCycle(material, robots, time);
    robots.geodeRobots++;

    int value = dfs(blueprint, material, robots, time, true, false, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, false, true, false, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, false, false, true, false);
    if (value > max)
      max = value;
    value = dfs(blueprint, material, robots, time, false, false, false, true);
    if (value > max)
      max = value;
  }

  return max;
}

void Day19::waitCycle(Material& material, Robots robots, int& time)
{
  if (time == 24)
  {
    return;
  }

  time++;

  material.ore += robots.oreRobots;
  material.clay += robots.clayRobots;
  material.obsidian += robots.obsidianRobots;
  material.geode += robots.geodeRobots;
}
