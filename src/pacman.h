#pragma once

#include <vector>
#include "SDL.h"

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

  Pacman(std::size_t grid_width, std::size_t grid_height);
  void update();
  bool alive();

  Direction direction = Direction::none;

  float x;
  float y;

 private:

  float speed_{0.1f};
  int const size_{1}; // TODO: determined by size of map
  bool alive_{true};
};
