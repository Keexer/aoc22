#pragma once

#include <vector>

class Day19
{
public:
  using Ore = int;
  using Clay = int;
  using Obsidian = int;
  using Geode = int;
  
  struct OreRobot
  {
    Ore oreCost{};
  };

  struct ClayRobot
  {
    Ore oreCost{};
  };

  struct ObsidianRobot
  {
    Ore oreCost{};
    Clay clayCost{};
  };

  struct GeodeRobot
  {
    Ore oreCost{};
    Obsidian obsidianCost{};
  };

  struct Blueprint
  {
    int number{};
    OreRobot oreRobot{};
    ClayRobot clayRobot{};
    ObsidianRobot obsidianRobot{};
    GeodeRobot geodeRobot{};
  };

  struct Robots
  {
    int oreRobots{1};
    int clayRobots{};
    int obsidianRobots{};
    int geodeRobots{};
  };

  struct Material
  {
    int ore{};
    int clay{};
    int obsidian{};
    int geode{};
  };

  using Data = std::vector<Blueprint>;
  Data extract();
  void solveA(Data&);
  void solveB(Data&);
  void solve();

  int dfs(const Blueprint& blueprint, Material material, Robots robots, int time, int maxTime, bool createOreRobot, bool createClayRobot, bool createObsidianRobot, bool createGeodeRobot);
  void waitCycle(Material& material, Robots robots, int& time, int maxTime);
};