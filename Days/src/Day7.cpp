#include "Days/Day7.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

namespace
{
  static constexpr size_t minSizeFolder = 100000;
  size_t combineSize(Directory& root)
  {
    for (auto& v : root.mDirs)
    {
      root.size += combineSize(v.second);
    }

    return root.size;
  }

  size_t sumA(Directory& root)
  {
    size_t sum{};
    for (auto v : root.mDirs)
    {
      sum += sumA(v.second);
    }

    if (root.size <= minSizeFolder)
    {
      sum += root.size;
    }

    return sum;
  }

  size_t findSmallestDirToDelete(Directory& root, size_t sizeToDelete, size_t min)
  {
    for (auto v : root.mDirs)
    {
      min = findSmallestDirToDelete(v.second, sizeToDelete, min);
    }

    if ((root.size >= sizeToDelete) && (root.size < min))
    {
      min = root.size;
    }

    return min;
  }
}

Directory Day7::extract()
{
  std::ifstream file("../../Input/Input7.txt");

  if (!file.is_open())
  {
    return {};
  }

  Directory root{ 0, {}, nullptr };
  Directory* currentDir{ &root };
  std::string line;

  while (std::getline(file, line))
  {
    if (line.at(0) == '$')
    {
      if (line.find("$ cd /") != std::string::npos)
      {
        currentDir = &root;
      }
      else if (line.find("$ cd ..") != std::string::npos)
      {
        if (currentDir->parent != nullptr)
        {
          currentDir = currentDir->parent;
        }
      }
      else if (line.find("$ cd") != std::string::npos)
      {
        static constexpr size_t cdSize = 5;
        std::string dir = line.substr(cdSize);
        currentDir = &currentDir->mDirs.at(dir);
      }
      else
      {}
    }
    else
    {
      std::string dirCmd = line.substr(0, 3);
      if (dirCmd.find("dir") != std::string::npos)
      {
        std::string dir = line.substr(4);
        currentDir->mDirs.insert({ dir, Directory{ 0, {}, currentDir } });
      }
      else if (line.at(0) >= '0' && line.at(0) <= '9')
      {
        std::string size = line.substr(0, line.find(' '));
        currentDir->size += std::stoi(size);
      }
      else
      {}
    }
  }

  combineSize(root);

  return root;
}

void Day7::solveA(Directory& input)
{
  size_t sum = sumA(input);
  std::cout << "Sum of total sizes of directories under 100000: " << sum << '\n';
}

void Day7::solveB(Directory& input)
{
  static constexpr size_t totalSize = 70000000;
  static constexpr size_t neededSpace = 30000000;
  const size_t toDelete = input.size - (totalSize - neededSpace);

  static constexpr size_t min{std::numeric_limits<size_t>::max()};
  size_t minDir = findSmallestDirToDelete(input, toDelete, min);

  std::cout << "The folder size to delete is: " << minDir << '\n';
}

void Day7::solve()
{
  auto dirStructure = extract();
  solveA(dirStructure);
  solveB(dirStructure);
}
