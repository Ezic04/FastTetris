#include "Tetromino.hpp"


Tetromino::Tetromino(Shape shape) : pos_y_(0), pos_x_(3)
{
  switch (shape)
  {
  case Shape::I:
    shape_size_ = 4;
    shape_matrix_(1, 0) = true;
    shape_matrix_(1, 1) = true;
    shape_matrix_(1, 2) = true;
    shape_matrix_(1, 3) = true;
    break;
  case Shape::O:
    shape_size_ = 2;
    shape_matrix_(0, 0) = true;
    shape_matrix_(0, 1) = true;
    shape_matrix_(1, 0) = true;
    shape_matrix_(1, 1) = true;
    pos_x_ = 4;
    break;
  case Shape::T:
    shape_size_ = 3;
    shape_matrix_(0, 1) = true;
    shape_matrix_(1, 0) = true;
    shape_matrix_(1, 1) = true;
    shape_matrix_(1, 2) = true;
    break;
  case Shape::S:
    shape_size_ = 3;
    shape_matrix_(1, 1) = true;
    shape_matrix_(1, 2) = true;
    shape_matrix_(2, 0) = true;
    shape_matrix_(2, 1) = true;
    break;
  case Shape::Z:
    shape_size_ = 3;
    shape_matrix_(1, 0) = true;
    shape_matrix_(1, 1) = true;
    shape_matrix_(2, 1) = true;
    shape_matrix_(2, 2) = true;
    break;
  case Shape::J:
    shape_size_ = 3;
    shape_matrix_(0, 0) = true;
    shape_matrix_(1, 0) = true;
    shape_matrix_(1, 1) = true;
    shape_matrix_(1, 2) = true;
    break;
  case Shape::L:
    shape_size_ = 3;
    shape_matrix_(0, 2) = true;
    shape_matrix_(1, 0) = true;
    shape_matrix_(1, 1) = true;
    shape_matrix_(1, 2) = true;
    break;
  }
}

void Tetromino::Rotate()
{
  ShapeMatrix result;
  size_t n_minus_1 = shape_size_ - 1;
  for (size_t i = 0; i < shape_size_; i++)
  {
    for (size_t j = 0; j < shape_size_; j++)
    {
      result(i, j) = shape_matrix_(j, n_minus_1 - i);
    }
  }
  shape_matrix_ = result;
}