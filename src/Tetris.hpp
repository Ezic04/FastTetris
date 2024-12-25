#pragma once
#include <atomic>
#include "BitMatrix.hpp"
#include "InputHandler.hpp"
#include "RandomComponent.hpp"
#include "Tetromino.hpp"

class Tetris
{
  constexpr static size_t kWidth_ = 10;
  constexpr static size_t kHeight_ = 20;
  constexpr static int fps = 5;
  using GridMatrix = BitMatrix<kHeight_,kWidth_>;
  GridMatrix grid_;
  std::atomic<bool> is_running_;
  InputHandler input_handler_;
  RandomComponent random_component_;
public:
  Tetris();
  void Run();
private:
  void MainLoop();
  void RemoveLines(const Tetromino& placed_block);
  bool HandleBlock(Tetromino& current_block);
  static void DrawGrid(const GridMatrix& grid);
  static void SleepForMilliseconds(int milliseconds);
  static bool DoesCollide(const Tetromino& tetromino, const GridMatrix& grid);
  static void TetrominoXor(const Tetromino& tetromino, GridMatrix& grid);
  template <typename Func>
  static void IterateOverTetromino(int8_t y, int8_t x, Func&& func);
};

template <typename Func>
void Tetris::IterateOverTetromino(int8_t y, int8_t x, Func&& func)
{
  for (size_t i = 0; i < Tetromino::Size(); i++)
  {
    for (size_t j = 0; j < Tetromino::Size(); j++)
    {
      bool inside_bounds = y + i < GridMatrix::GetM() and x + j < GridMatrix::GetN();
      func(i, j, inside_bounds);
    }
  }
}

