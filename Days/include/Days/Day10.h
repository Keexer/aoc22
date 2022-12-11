#pragma once

#include <deque>
#include <memory>

struct Operation
{
  virtual int run() = 0;
  virtual bool done() = 0;
};

struct NOOP : Operation
{
  virtual int run() override { return 0; };
  virtual bool done() override { return true; };
};

struct Add : Operation
{
  Add(int V)
    : mV{ V }
    , mFirst{ true }
  {}

  virtual int run() override
  {
    if (mFirst)
    {
      mFirst = false;
      return 0;
    }

    mDone = true;
    return mV;
  }

  virtual bool done() override
  {
    return mDone;
  }

private:
  int mV;
  bool mFirst;
  bool mDone{ false };
};

class Day10
{
public:
  using Ops = std::deque<std::unique_ptr<Operation> >;
  Ops extract();
  void solveA(Ops& op);
  void solveB(Ops& op);
  void solve();
};