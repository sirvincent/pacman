#include "pacman.h"
#include <cmath>
#include <iostream>


// TODO: should this be screen width/height?
Pacman::Pacman(std::size_t grid_width, std::size_t grid_height) :
  x(grid_width / 2), y(grid_height / 2) {}

void Pacman::update()
{
  switch (direction)
  {
    case Direction::kUp:
      y -= speed_;
      break;
    case Direction::kDown:
      y += speed_;
      break;
    case Direction::kLeft:
      x -= speed_;
      break;
    case Direction::kRight:
      x += speed_;
      break;
  }
  // TODO: check if new x,y in side screen
}

bool Pacman::alive()
{
  return true;
}
