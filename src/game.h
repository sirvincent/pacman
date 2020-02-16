#pragma once

#include "controller.h"
#include "renderer.h"
#include "dot.h"
#include "pacman.h"
#include "level.h"

#include "SDL.h"


class Game {
public:
  Game(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height);
  void run(Controller const &controller, Renderer &renderer,
           uint32_t const target_frame_duration);
  int score() const;
  int getSize() const;

private:
  bool checkRectangleCollision(SDL_FRect const &rectangle, std::vector<SDL_Rect> &other);
  bool checkRectangleCollision(SDL_FRect const &rectangle, SDL_Rect const &other);

  void handlePacmanDotCollisions(Pacman const &pacman, std::vector<Dot> &dots);

  std::size_t screen_width_;
  std::size_t screen_height_;
  std::size_t grid_width_;
  std::size_t grid_height_;

  Pacman pacman_;
  std::vector<Dot> dots_;
  std::vector<Dot> pellets_;
  std::vector<SDL_Rect> walls_;



  int score_{0};
  static unsigned int constexpr time_between_title_update_{1000};

  void update();
};
