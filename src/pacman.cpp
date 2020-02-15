#include "pacman.h"
#include <cmath>
#include <iostream>


// TODO: should this be screen width/height?
Pacman::Pacman(std::size_t screen_to_grid_width, std::size_t screen_to_grid_height) :
  x(screen_to_grid_width / 2), y(screen_to_grid_height / 2) {}


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
  // TODO: check if new x,y in side screen
}

bool Pacman::alive()
{
  return true;
}
