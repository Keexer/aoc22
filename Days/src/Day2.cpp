#include "Days/Day2.h"

#include <sstream>
#include <fstream>
#include <iostream>

int shapeScore(char shape)
{
    return shape - 'W';
}

Day2::Cont Day2::extract()
{
    Cont guide {};

    std::ifstream file;
    file.open("../../Input/Input2.txt");

    if (!file.is_open())
    {
        return {};
    }

    std::string line;
    while (std::getline(file, line))
    {
        guide.push_back({ line[0], line[2] });
    }

    return guide;
}

void Day2::solveA(Day2::Cont& cont)
{
    static constexpr int win = 6;
    static constexpr int draw = 3;

    int score{};
    
    for (auto v : cont)
    {
        score += shapeScore(v.second);
        if (v.first - 'A' == v.second - 'X') // draw
        {
            score += draw;
            continue;
        }

        switch (v.first)
        {
        case 'A': // rock
            if (v.second == 'Y')
            {
                score += win;
            }
            break;
        case 'B': // paper
            if (v.second == 'Z')
            {
                score += win;
            }
            break;
        case 'C': // scissor
            if (v.second == 'X')
            {
                score += win;
            }
            break;
        }
    }

    std::cout << "First task: Total score = " << score << '\n';
}

void Day2::solveB(Day2::Cont& cont)
{
    static constexpr int win = 6;
    static constexpr int draw = 3;

    int score{};

    for (auto v : cont)
    {
        switch (v.second)
        {
        case 'X':
            switch (v.first)
            {
            case 'A':
                score += 3;
                break;
            case 'B':
                score += 1;
                break;
            case 'C':
                score += 2;
                break;
            }
            break;
        case 'Y':
            score += draw;
            score += v.first - '@';
            break;
        case 'Z':
            score += win;
            switch (v.first)
            {
            case 'A':
                score += 2;
                break;
            case 'B':
                score += 3;
                break;
            case 'C':
                score += 1;
                break;
            }
            break;
        }
    }

    std::cout << "Second task: New total score = " << score << '\n';
}

void Day2::solve()
{
    auto data = extract();
    solveA(data);
    solveB(data);
}
