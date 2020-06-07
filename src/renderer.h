#pragma once

#include "pacman.h"
#include "dot.h"
#include "ghost.h"

#include "SDL.h"

#include <vector>
#include <memory>


class Renderer
{
public:
  Renderer(const std::size_t screenWidth_, const std::size_t screenHeight_, const std::size_t gridWidth_, const std::size_t gridHeight_);
  ~Renderer();

  void initialize(Pacman &pacman, std::vector<std::unique_ptr<Ghosts::Ghost>> const &ghosts, std::filesystem::path const &executablePath);
  void render(Pacman &pacman, std::vector<Dot> const &dots, std::vector<Dot> const &pellets, std::vector<SDL_Rect> const &walls, std::vector<std::unique_ptr<Ghosts::Ghost>> const &ghosts);
  void updateWindowTitle(int score, int fps);

private:
  SDL_Window *sdlWindow_;
  SDL_Renderer *sdlRenderer_;

  const std::size_t screenWidth_;
  const std::size_t screenHeight_;
  const std::size_t gridWidth_;
  const std::size_t gridHeight_;
};
