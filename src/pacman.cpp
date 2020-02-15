#include "pacman.h"
#include <cmath>
#include <iostream>


Pacman::Pacman(std::size_t position_x, std::size_t position_y, std::size_t pacman_width, std::size_t pacman_height) :
  x(position_x), y(position_y), width(pacman_width), height(pacman_height) {}

void Pacman::move_x()
{
  // TODO: currently movement is frame based, I prefer time based for understandable physics
  x += velocity_x;
}

void Pacman::move_y()
{
  y += velocity_y;
}

bool Pacman::alive()
{
  return true;
}
