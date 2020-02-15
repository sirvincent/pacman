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
  bool alive();

  Direction direction = Direction::none;

  float x;
  float y;

  std::size_t const width;
  std::size_t const height;

 private:
  float speed_{2.5f};
  bool alive_{true};

};
