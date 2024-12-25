#pragma once
#include "BitMatrix.hpp"
#include "Matrix.hpp"

class Tetromino
{
  static constexpr size_t N = 4;
  using ShapeMatrix = BitMatrix<N, N>;
  ShapeMatrix shape_matrix_;
  uint8_t shape_size_;
  int8_t pos_y_;
  int8_t pos_x_;
public:
  enum class Shape { I, O, T, J, L, S, Z };
  Tetromino() = delete;
  Tetromino(const Tetromino& other) = default;
  Tetromino(Tetromino&& other) = default;
  Tetromino& operator=(const Tetromino& other) = default;
  Tetromino& operator=(Tetromino&& other) = default;
  explicit Tetromino(Shape shape);
  ~Tetromino() = default;
  bool operator()(size_t i, size_t j) const { return shape_matrix_(i, j); }
  std::bitset<N> operator[](size_t i) const { return shape_matrix_[i]; }
  static consteval size_t Size() { return N; }
  int8_t GetY() const { return pos_y_; }
  int8_t GetX() const { return pos_x_; }
  void MoveDown() { ++pos_y_; }
  void MoveLeft() { --pos_x_; }
  void MoveRight() { ++pos_x_; }
  void Rotate();
};
