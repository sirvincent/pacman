#pragma once

#include "pacman.h"
#include "dot.h"

#include "SDL.h"

#include <vector>

class Renderer {
 public:
  Renderer(const std::size_t screen_width_, const std::size_t screen_height_,
           const std::size_t grid_width_, const std::size_t grid_height_);
  ~Renderer();

  void render(Pacman const &pacman, std::vector<Dot> const & dots_);
  void updateWindowTitle(int score, int fps);

 private:

  SDL_Window *sdl_window_;
  SDL_Renderer *sdl_renderer_;

  const std::size_t screen_width_;
  const std::size_t screen_height_;
  const std::size_t grid_width_;
  const std::size_t grid_height_;


};
