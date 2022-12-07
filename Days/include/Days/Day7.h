#pragma once

#include <map>
#include <string>

struct Directory
{
  size_t size{};
  std::map<std::string, Directory> mDirs;
  Directory* parent{ nullptr };
};

class Day7
{
public:
  Directory extract();
  void solveA(Directory& input);
  void solveB(Directory& input);
  void solve();
};
