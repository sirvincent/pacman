#include "pacman.h"

#include <cmath>
#include <iostream>
#include <array>


// TODO: a magic string, do we want to make this settable?
//       set in Data::Pacman
Pacman::Pacman(float width, float height)
  : Movement(Data::Pacman::speed, Data::Pacman::speed, Data::Pacman::speed, Data::Pacman::speed)
  , Implementation::Animation("pac-classic/pac-classic_c-toy.png", SDL_GetTicks(), Data::Pacman::animations, "left")
{
  // x,y are initialized to 0.0f to circumvent uninitialized members
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;

  current_ms_since_start_ = SDL_GetTicks();
}

void Pacman::move()
{
  // TODO: currently movement is frame based, I prefer time based for understandable physics}
  x += velocityX_;
  y += velocityY_;
}

bool Pacman::alive() const
{
  return alive_;
}

void Pacman::alive(bool alive)
{
  alive_ = alive;
}

std::string Pacman::onActiveSprite()
{
  switch (direction)
  {
    case Movement::Direction::up:
      return "up";
      break;
    case Movement::Direction::down:
      return "down";
      break;
    case Movement::Direction::left:
      return "left";
      break;
    case Movement::Direction::right:
      return "right";
      break;
    default:
      throw "unhandled direction";
  }
}
