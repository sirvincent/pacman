#pragma once

#include <vector>
#include "SDL.h"

class Pacman {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Pacman(std::size_t grid_width, std::size_t grid_height);
  void update();
  bool alive();

  Direction direction = Direction::kUp;

  float x;
  float y;

 private:

  float speed_{0.1f};
  int const size_{1}; // TODO: determined by size of map
  bool alive_{true};
};
