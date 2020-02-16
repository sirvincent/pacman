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

  void move();
  void adjust_x_y_velocity_on_direction(Direction direction_to_go_to);
  bool alive();

  // TODO: I do not like that almost everything is public! make privates and setters and getters

  static float constexpr velocity{2.0f};

  float velocity_x{velocity};
  float velocity_y{velocity};

  Direction direction = Direction::left;
  Direction wanted_direction = direction;

private:
  bool alive_{true};
};
