#pragma once

#include "movement.h"

#include "SDL.h"

#include <vector>


class Pacman : public SDL_FRect, public Movement
{
public:
  Pacman(float width, float height, float speed);

  void move();

  bool alive() const;
  void alive(bool alive);

private:
  bool alive_{true};
};


