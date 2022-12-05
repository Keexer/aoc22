#include "Days/Day3.h"

#include <sstream>
#include <fstream>
#include <iostream>

namespace
{
    int getPriority(char val)
    {
        if (val < 'a') // Capital letter
        {
            return val - 'A' + 1 + 26;
        }
        else
        {
            return val - 'a' + 1;
        }
    }
}

std::vector<std::string> Day3::extract()
{
    std::ifstream file;
    file.open("../../Input/Input3.txt");

    if (!file.is_open())
    {
        return {};
    }

    std::vector<std::string> stringList;
    std::string line;
    while (std::getline(file, line))
    {
        stringList.push_back(line);
    }

    return stringList;
}

void Day3::solveA(std::vector<std::string>& vec)
{
    int sum{};
    for (auto v : vec)
    {
        std::string first = v.substr(0, v.size() / 2);
        std::string second = v.substr(v.size() / 2);

        for (auto character : first)
        {
            if (second.find(character) != std::string::npos)
            {
                sum += getPriority(character);
                break;
            }
        }
    }

    std::cout << "Sum of priorities: " << sum << '\n';
}

void Day3::solveB(std::vector<std::string>& vec)
{
    int line{};
    std::vector<std::vector<std::string> > groups;
    while (line + 2 < vec.size())
    {
        groups.push_back({vec[line], vec[++line], vec[++line]});
        ++line;
    }

    int sum{};

    for (auto v : groups)
    {
        for (auto character : v[0])
        {
            bool existInSecond = v[1].find(character) != std::string::npos;
            bool existInThird = v[2].find(character) != std::string::npos;
            if (existInSecond && existInThird)
            {
                sum += getPriority(character);
                break;
            }
        }
    }

    std::cout << "Sum of priority badges = " << sum << '\n';
}

void Day3::solve()
{
    auto stringList = extract();
    solveA(stringList);
    solveB(stringList);
}
