#pragma once
#include <array>
#include <ostream>

template <typename T, size_t M, size_t N>
class Matrix
{
  std::array<std::array<T, N>, M> matrix_;
public:
  Matrix();
  ~Matrix() = default;
  Matrix(const Matrix& other);
  Matrix(Matrix&& other) = default;
  Matrix& operator=(const Matrix& other) = default;
  Matrix& operator=(Matrix&& other) = default;
  T& operator()(size_t i, size_t j) { return matrix_[i][j]; }
  const T& operator()(size_t i, size_t j) const { return matrix_[i][j]; }
  std::array<T, N>& operator[](size_t i) { return matrix_[i]; }
  const std::array<T, N>& operator[](size_t i) const { return matrix_[i]; }
  friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
  static consteval size_t GetM() { return M; }
  static consteval size_t GetN() { return N; }
};

template <typename T, size_t M, size_t N>
Matrix<T, M, N>::Matrix()
{
  for (size_t i = 0; i < M; i++)
  {
    for (size_t j = 0; j < N; j++)
    {
      matrix_[i][j] = T();
    }
  }
}

template <typename T, size_t M, size_t N>
Matrix<T, M, N>::Matrix(const Matrix& other)
{
  for (size_t i = 0; i < M; i++)
  {
    for (size_t j = 0; j < N; j++)
    {
      matrix_[i][j] = other(i, j);
    }
  }
}


template <typename T, size_t M, size_t N>
std::ostream& operator<<(std::ostream& os, const Matrix<T, M, N>& matrix)
{
  for (size_t i = 0; i < M; i++)
  {
    for (size_t j = 0; j < N; j++)
    {
      os << matrix(i, j) << ' ';
    }
    os << '\n';
  }
  return os;
}