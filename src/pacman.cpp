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

void Pacman::update()
{
  // TODO: currently movement is frame based, I prefer time based for understandable physics
  switch (direction)
  {
    case Direction::up:
      velocity_y = -velocity;
      velocity_x = 0;
      break;
    case Direction::down:
      velocity_y = velocity;
      velocity_x = 0;
      break;
    case Direction::left:
      velocity_y = 0;
      velocity_x = -velocity;
      break;
    case Direction::right:
      velocity_y = 0;
      velocity_x = velocity;
      break;
  }
  x += velocity_x;
  y += velocity_y;
}

bool Pacman::alive()
{
  return true;
}
