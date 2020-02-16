#pragma once

#include "movement.h"

#include "SDL.h"

#include <vector>


class Pacman : public SDL_FRect, public Movement
{
public:
  Pacman(float width, float height, float speed);

  void move();
  bool alive();

  Movement::Direction direction = Movement::Direction::left;
  Movement::Direction wanted_direction = direction;

private:
  bool alive_{true};
};
