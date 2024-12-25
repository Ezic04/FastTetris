#pragma once
#include <random>
#include <stack>
#include "Tetromino.hpp"

class RandomComponent
{
  std::stack<Tetromino::Shape> random_stack_;
  std::random_device rd_;
  std::mt19937 g_;
public:
  Tetromino::Shape RandomShape();
};
