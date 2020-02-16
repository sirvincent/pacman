#pragma once

#include "SDL.h"

#include <vector>

enum class Direction : uint8_t
  {
    up,
    down,
    left,
    right
  };

class Pacman : public SDL_FRect
{
public:
  Pacman(float width, float height);
  void update();
  bool alive();

  // TODO: I do not like that almost everything is public! make privates and setters and getters

  static float constexpr velocity{2.0f};

  float velocity_x{velocity};
  float velocity_y{velocity};

  Direction direction = Direction::left;

private:
  bool alive_{true};
};
