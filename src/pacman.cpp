#include "pacman.h"
#include "image_loader.h"

#include <cmath>
#include <iostream>


// TODO: a magic string, do we want to make this settable?
Pacman::Pacman(float width, float height, float speed) : Movement(speed, speed, speed, speed),
                                                         Implementation::SpriteGraphics("pac-classic/pac-classic_c-toy.png")
{
  // x,y are initialized to 0.0f to circumvent uninitialized members
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
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

std::pair<SDL_Texture *, SDL_Rect> Pacman::activeSprite()
{
  switch (direction)
  {
    case Movement::Direction::up:
      return std::make_pair(spriteSheet_, SDL_Rect{556, 853, 138, 170});
      break;
    case Movement::Direction::down:
      return std::make_pair(spriteSheet_, SDL_Rect{556, 5, 138, 170});
      break;
    case Movement::Direction::left:
      return std::make_pair(spriteSheet_, SDL_Rect{556, 342, 138, 170});
      break;
    case Movement::Direction::right:
      return std::make_pair(spriteSheet_, SDL_Rect{556, 172, 138, 170});
      break;
  }
}
