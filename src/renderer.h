#pragma once

#include "pacman.h"
#include "dot.h"
#include "ghost.h"

#include "SDL.h"

#include <vector>
#include <memory>


class Renderer {
public:
  Renderer(const std::size_t screen_width_, const std::size_t screen_height_,
           const std::size_t grid_width_, const std::size_t grid_height_);
  ~Renderer();

  void initialize(Pacman &pacman, std::vector<std::unique_ptr<Ghosts::Ghost>> const &ghosts, std::filesystem::path const &executable_path);
  void render(Pacman &pacman, std::vector<Dot> const &dots, std::vector<Dot> const &pellets,
              std::vector<SDL_Rect> const &walls, std::vector<std::unique_ptr<Ghosts::Ghost>> const &ghosts);
  void updateWindowTitle(int score, int fps);

private:
  SDL_Window *sdl_window_;
  SDL_Renderer *sdl_renderer_;

  const std::size_t screen_width_;
  const std::size_t screen_height_;
  const std::size_t grid_width_;
  const std::size_t grid_height_;


};
