#pragma once

#include <string>
#include <vector>
#include <algorithm>

using Shape = std::vector<std::vector<bool> >;

struct IShape
{
  virtual Shape getShape() = 0;
};

struct MinusShape : IShape
{
  Shape getShape() final {
    return shape;
  }
  std::vector<std::vector<bool> > shape{
    {true, true, true, true}
  };
};

struct PlusShape : IShape
{
  Shape getShape() final {
    return shape;
  }
  std::vector<std::vector<bool> > shape{
    {false, true, false},
    {true, true, true},
    {false, true, false}
  };
};

struct LShape : IShape
{
  Shape getShape() final {
    return shape;
  }
  std::vector<std::vector<bool> > shape{
    {false, false, true},
    {false, false, true},
    {true, true, true}
  };
};

struct PipeShape : IShape
{
  Shape getShape() final {
    return shape;
  }
  std::vector<std::vector<bool> > shape{
    {true},
    {true},
    {true},
    {true}
  };
};

struct SquareShape : IShape
{
  Shape getShape() final {
    return shape;
  }
  std::vector<std::vector<bool> > shape{
    {true, true},
    {true, true}
  };
};

struct Rock
{
  Rock(IShape* shape)
    : mShape(shape)
    , height(mShape->getShape().size())
    , width(mShape->getShape().front().size())
  {
    std::vector<bool> rockRow(7, false);
    for (size_t i = 0; i < height; i++)
    {
      rock.push_back(rockRow);
    }

    for (size_t i = 0; i < height; ++i)
    {
      for (size_t j = 0; j < width; j++)
      {
        rock[i][j+2] = mShape->getShape()[height - 1 - i][j];
      }
    }
  }

  void moveLeft(std::vector<std::vector<bool> >& map)
  {
    bool canMove = true;
    for (size_t i = 0; i < height; i++)
    {
      if (rock[i][0])
      {
        canMove = false;
        break;
      }
    }

    for (size_t j = 0; j < height && canMove; ++j)
    {
      for (size_t i = 1; i < map.front().size(); ++i)
      {
        if (rock[j][i])
        {
          if (map[mOriginY + j][i - 1])
          {
            canMove = false;
          }
          break;
        }
      }
    }

    if (canMove)
    {
      for (size_t i = 0; i < height; ++i)
      {
        for (size_t j = 0; j < 6; j++)
        {
          rock[i][j] = rock[i][j + 1];
          rock[i][j + 1] = false;
        }
      }
    }
  }

  void moveRight(std::vector<std::vector<bool> >& map)
  {
    bool canMove = true;
    for (size_t i = 0; i < height; ++i)
    {
      if (rock[i][6])
      {
        canMove = false;
        break;
      }
    }

    for (size_t j = 0; j < height && canMove; ++j)
    {
      for (size_t i = static_cast<int>(map.front().size()) - 2; i >= 0; --i)
      {
        if (rock[j][i])
        {
          if (map[mOriginY + j][i + 1])
          {
            canMove = false;
          }
          break;
        }
      }
    }

    if (canMove)
    {
      for (size_t i = 0; i < height; ++i)
      {
        for (int j = 5; j >= 0; --j)
        {
          rock[i][j + 1] = rock[i][j];
          rock[i][j] = false;
        }
      }
    }
  }

  void moveDown()
  {
    mOriginY--;
  }

  bool isLanded(std::vector<std::vector<bool> >& map)
  {
    for (size_t k = 0; k < height; ++k)
    {
      for (int i = static_cast<int>(map.size()) - 1; i >= static_cast<int>(mOriginY); i--)
      {
        if (std::find(map[i - 1].begin(), map[i - 1].end(), true) != map[i - 1].end())
        {
          if (static_cast<int>(mOriginY) == i)
          {
            for (size_t j = 0; j < map.front().size(); j++)
            {
              if (map[i - 1][j])
              {
                if (rock[0][j])
                {
                  return true;
                }
              }
            }
          }
          // Handle plus sign
          if (static_cast<int>(mOriginY) + 1 == i && height > 1)
          {
            for (size_t j = 0; j < map.front().size(); j++)
            {
              if (map[i - 1][j])
              {
                if (rock[1][j])
                {
                  return true;
                }
              }
            }
          }
        }
      }
    }

    return false;
  }

  void setStart(size_t originY)
  {
    mOriginY = originY;
  }

  void saveToMap(std::vector<std::vector<bool> >& map)
  {
    size_t index{};
    for (size_t i = mOriginY; i < mOriginY + height; i++)
    {
      for (size_t j = 0; j < map.front().size(); j++)
      {
        map[i][j] = map[i][j] || rock[index][j];
      }
      index++;
    }
  }

  IShape* mShape;
  std::vector<std::vector<bool> > rock;
  size_t height;
  size_t width;
  size_t mOriginY;
};

class Day17
{
public:
  void init()
  {
    row.assign(7, false);
    map.assign(4, row);
    
    for (size_t i = 0; i < map.front().size(); i++)
    {
      map[0][i] = true;
    }

    shapes.push_back(&m);
    shapes.push_back(&p);
    shapes.push_back(&l);
    shapes.push_back(&pi);
    shapes.push_back(&s);
  }

  using Input = std::string;
  Input extract();
  void solveA(Input&);
  void solveB(Input&);
  void solve();

  MinusShape m{};
  PlusShape p{};
  LShape l{};
  PipeShape pi{};
  SquareShape s{};
  std::vector<IShape*> shapes;

  std::vector<bool> row;
  std::vector<std::vector<bool> > map;
};