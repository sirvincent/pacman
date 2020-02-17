#include "pacman.h"
#include <cmath>
#include <iostream>


Pacman::Pacman(float width, float height, float speed) :
  Movement(speed, speed, speed, speed)
{
  // x,y are initialized to 0.0f since I want to circumvent uninitialized members
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}

void Pacman::move()
{
  // TODO: currently movement is frame based, I prefer time based for understandable physics}

  x += velocity_x_;
  y += velocity_y_;
}

bool Pacman::alive() const
{
  return alive_;
}

void Pacman::alive(bool alive)
{
  alive_ = alive;
}
