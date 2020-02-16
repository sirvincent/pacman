#pragma once

#include "SDL.h"

#include <vector>

class Pacman : public SDL_FRect
{
public:
  Pacman(float width, float height);
  void move_x();
  void move_y();
  bool alive();

  // TODO: I do not like that almost everything is public! make privates and setters and getters

  static float constexpr velocity{2.0f};

  float velocity_x{0.0f};
  float velocity_y{0.0f};

private:
  bool alive_{true};
};
