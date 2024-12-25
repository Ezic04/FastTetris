#pragma once
#include <array>
#include <bitset>

template < size_t M, size_t N>
class BitMatrix
{
  std::array<std::bitset<N>, M> matrix_;
public:
  BitMatrix() = default;
  ~BitMatrix() = default;
  BitMatrix(const BitMatrix& other) = default;
  BitMatrix(BitMatrix&& other) = default;
  BitMatrix& operator=(const BitMatrix& other) = default;
  BitMatrix& operator=(BitMatrix&& other) = default;
  typename std::bitset<N>::reference operator()(size_t i, size_t j) { return matrix_[i][j]; }
  bool operator()(size_t i, size_t j) const { return matrix_[i][j]; }
  std::bitset<N>& operator[](size_t i) { return matrix_[i]; }
  const std::bitset<N>& operator[](size_t i) const { return matrix_[i]; }
  static consteval size_t GetM() { return M; }
  static consteval size_t GetN() { return N; }
};
