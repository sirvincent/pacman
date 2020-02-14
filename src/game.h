#pragma once

#include "controller.h"
#include "renderer.h"
#include "pacman.h"

#include "SDL.h"


class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void run(Controller const &controller, Renderer &renderer,
           uint32_t const target_frame_duration);
  int score() const;
  int getSize() const;

private:
  Pacman pacman_;
  SDL_Point dot_;

  int score_{0};

  void update();
};
