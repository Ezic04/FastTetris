#include "RandomComponent.hpp"

Tetromino::Shape RandomComponent::RandomShape()
{
  if (random_stack_.empty())
  {
    std::array shapes =
    {
      Tetromino::Shape::I, Tetromino::Shape::O, Tetromino::Shape::T,
      Tetromino::Shape::J, Tetromino::Shape::L, Tetromino::Shape::S, Tetromino::Shape::Z
    };
    std::ranges::shuffle(shapes, g_);
    for (auto& shape : shapes)
    {
      random_stack_.emplace(shape);
    }
  }
  Tetromino::Shape shape = random_stack_.top();
  random_stack_.pop();
  //return Tetromino::Shape::I;
  return shape;
}
