#include "Days/Day6.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace
{

  void findMarkers(std::string input, size_t markerSize)
  {
    for (size_t i = 0; i < (input.size() - (markerSize - 1)); ++i)
    {
      std::string marker{};
      for (size_t j = 0; j < markerSize; ++j)
      {
        char temp = input.at(i + j);
        if (marker.find(temp) == std::string::npos)
        {
          marker.push_back(temp);
        }
        else
        {
          marker.clear();
          break;
        }
      }

      if (marker.size() > 0) // Found marker
      {
        std::cout << "First marker after character: " << i + markerSize << '\n';
        break;
      };
    }
  }

}

std::string Day6::extract()
{
  std::ifstream file("../../Input/Input6.txt");

  if (!file.is_open())
  {
    return {};
  }

  std::string input;
  std::getline(file, input);

  return input;
}

void Day6::solveA(std::string input)
{
  static constexpr size_t aMarkerSize = 4;
  findMarkers(input, aMarkerSize);
}

void Day6::solveB(std::string input)
{
  static constexpr size_t bMarkerSize = 14;
  findMarkers(input, bMarkerSize);
}

void Day6::solve()
{
  auto data = extract();
  solveA(data);
  solveB(data);
}
