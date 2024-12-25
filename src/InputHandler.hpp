#pragma once
#include <atomic>
#include <functional>
#include <mutex>

#include "Tetromino.hpp"


class InputHandler
{
  static constexpr uint8_t kMoveSize = 3;
  inline static std::array<std::function<void(Tetromino&)>, 3> kInitMoves = { &Tetromino::MoveDown, nullptr, nullptr };
  const std::atomic<bool>& is_running_;
  std::mutex mtx_;
  std::array<std::function<void(Tetromino&)>, kMoveSize> moves_queue_;
public:
  explicit InputHandler(std::atomic<bool>& is_running) : is_running_(is_running), moves_queue_(kInitMoves) {}
  void operator()();
  std::array<std::function<void(Tetromino&)>, kMoveSize> GetMoves();
};
