#pragma once

#include "SDL.h"

#include <vector>

class Pacman {
 public:
  enum class Direction
  {
    up,
    down,
    left,
    right,
    none
  };

  Pacman(std::size_t position_x, std::size_t position_y, std::size_t pacman_width, std::size_t pacman_height);
  void update();
  void move();
  bool alive();

  Direction direction = Direction::none;

  // TODO: I do not like that almost everything is public! make privates and setters and getters
  float x;
  float y;

  std::size_t const width;
  std::size_t const height;

  static float constexpr velocity{2.5f};

  float velocity_x{0.0f};
  float velocity_y{0.0f};

 private:

  bool alive_{true};

};
