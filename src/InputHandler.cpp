#include "InputHandler.hpp"

#include <conio.h>

void InputHandler::operator()()
{
  while (is_running_)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    int key = _getch();
    if (key == 0 or key == 224)
    {
      key = _getch();
      std::lock_guard lock(mtx_);
      switch (key)
      {
      case 72: //up
        moves_queue_[1] = &Tetromino::Rotate;
        break;
      case 80: //down
        moves_queue_[1] = &Tetromino::MoveDown;
        break;
      case 75: //left
        if (moves_queue_[2] != nullptr and *moves_queue_[2].target<void (Tetromino::*)()>() == &Tetromino::MoveLeft)
        {
          moves_queue_[1] = &Tetromino::MoveLeft;
          break;
        }
        moves_queue_[2] = &Tetromino::MoveLeft;
        break;
      case 77: //right
        if (moves_queue_[2] != nullptr and *moves_queue_[2].target<void (Tetromino::*)()>() == &Tetromino::MoveRight)
        {
          moves_queue_[1] = &Tetromino::MoveRight;
          break;
        }
        moves_queue_[2] = &Tetromino::MoveRight;
        break;
      }
    }
    while (_kbhit())
    {
      _getch();
    }
  }
}

std::array<std::function<void(Tetromino&)>, 3> InputHandler::GetMoves()
{
  std::lock_guard lock(mtx_);
  auto temp = moves_queue_;
  moves_queue_ = kInitMoves;
  return temp;
}
