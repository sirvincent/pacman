#include "pacman.h"
#include <cmath>
#include <iostream>


Pacman::Pacman(std::size_t position_x, std::size_t position_y, std::size_t pacman_width, std::size_t pacman_height) :
  x(position_x), y(position_y), width(pacman_width), height(pacman_height) {}


void Pacman::update()
{
  switch (direction)
  {
    case Direction::up:
      y -= speed_;
      break;
    case Direction::down:
      y += speed_;
      break;
    case Direction::left:
      x -= speed_;
      break;
    case Direction::right:
      x += speed_;
      break;
    case Direction::none:
      break;
  }
}

bool Pacman::alive()
{
  return true;
}
