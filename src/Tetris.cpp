#include "Tetris.hpp"

#include <iostream>
#include <queue>
#include <random>
#include <thread>

Tetris::Tetris() : is_running_(false), input_handler_(is_running_)
{
}

void Tetris::Run()
{
  is_running_ = true;
  MainLoop();
}

void Tetris::MainLoop()
{
  std::thread input_thread(std::ref(input_handler_));
  while (is_running_)
  {
    Tetromino current_block(random_component_.RandomShape());
    is_running_ = HandleBlock(current_block);
    RemoveLines(current_block);
  }
  input_thread.join();
}

void Tetris::RemoveLines(const Tetromino& placed_block)
{
  const uint8_t y = placed_block.GetY();
  std::bitset<Tetromino::Size()> to_remove;
  for (size_t i = 0; i < Tetromino::Size(); i++)
  {
    if (kHeight_ <= y + i)
    {
      break;
    }
    to_remove[i] = true;
    for (size_t j = 0; j < kWidth_; j++)
    {
      if (!grid_(y + i, j))
      {
        to_remove[i] = false;
        break;
      }
    }
  }
  uint8_t remove_count = to_remove.count();
  if (remove_count == 0)
  {
    return;
  }
  std::bitset<kWidth_> empty_row{};
  std::queue<std::bitset<kWidth_>> rows_queue;
  for (size_t i = 0; i < remove_count; i++)
  {
    rows_queue.emplace(empty_row);
  }
  for (size_t i = 0; i < y; i++)
  {
    rows_queue.emplace(grid_[i]);
    grid_[i] = rows_queue.front();
    rows_queue.pop();
  }
  for (size_t i = 0; i < Tetromino::Size(); i++)
  {
    if (y + i >= kHeight_) break;
    if (!to_remove[i])
    {
      rows_queue.emplace(grid_[y + i]);
    }
    grid_[y + i] = rows_queue.front();
    rows_queue.pop();
  }
}

bool Tetris::HandleBlock(Tetromino& current_block)
{
  if (DoesCollide(current_block, grid_))
  {
    return false;
  }
  constexpr int mspf = 1000 / fps; //milliseconds per frame
  GridMatrix grid_copy = grid_;
  bool is_falling = true;
  auto print_block_on_grid = [&]
    {
      TetrominoXor(current_block, grid_copy);
      DrawGrid(grid_copy);
      TetrominoXor(current_block, grid_copy);
      SleepForMilliseconds(mspf);
      system("cls");
    };
  print_block_on_grid();
  while (is_falling)
  {
    auto moves = input_handler_.GetMoves();
    int move_count = 0;
    for (auto& move : moves)
    {
      if (move == nullptr)
      {
        continue;
      }
      Tetromino block_copy = current_block;
      move(block_copy);
      if (!DoesCollide(block_copy, grid_copy))
      {
        ++move_count;
        current_block = block_copy;
      }
    }
    if (!move_count)
    {
      is_falling = false;
    }
    print_block_on_grid();
  }
  TetrominoXor(current_block, grid_);
  return true;
}

void Tetris::DrawGrid(const GridMatrix& grid)
{
  for (size_t i = 0; i < kHeight_; i++)
  {
    for (size_t j = 0; j < kWidth_; j++)
    {
      std::cout << (grid(i, j) ? 'x' : '.');
    }
    std::cout << '\n';
  }
}

void Tetris::SleepForMilliseconds(int milliseconds)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

bool Tetris::DoesCollide(const Tetromino& tetromino, const GridMatrix& grid)
{
  const int8_t y = tetromino.GetY();
  const int8_t x = tetromino.GetX();
  bool collision = false;
  IterateOverTetromino(y, x, [&](size_t i, size_t j, bool insideBounds)
    {
      if (insideBounds)
      {
        if (grid(y + i, x + j) and tetromino(i, j))
        {
          collision = true;
        }
      }
      else if (tetromino(i, j))
      {
        collision = true;
      }
    });

  return collision;
}

void Tetris::TetrominoXor(const Tetromino& tetromino, GridMatrix& grid)
{
  const int8_t y = tetromino.GetY();
  const int8_t x = tetromino.GetX();
  for (size_t i = 0; i < Tetromino::Size() ; i++)
  {
    if (y + i >= kHeight_) break;
    std::bitset<Tetromino::Size()> tetromino_row = tetromino[i];
    if (x >= 0)
    {
      grid[y + i] ^= std::bitset<kWidth_>(tetromino_row.to_ulong()) << x;
    }
    else
    {
      grid[y + i] ^= std::bitset<kWidth_>(tetromino_row.to_ulong()) >> -x;
    }
  }
}