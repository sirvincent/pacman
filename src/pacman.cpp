#include "pacman.h"
#include <cmath>
#include <iostream>


Pacman::Pacman(float width, float height)
{
  // x,y are initialized to 0.0f since I want to circumvent uninitialized members
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}

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
