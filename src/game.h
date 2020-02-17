#pragma once

#include "controller.h"
#include "renderer.h"
#include "dot.h"
#include "pacman.h"
#include "ghost.h"
#include "level.h"

#include "SDL.h"

#include <memory>


class Game {
public:
  Game(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height);
  void run(Controller const &controller, Renderer &renderer,
           uint32_t const target_frame_duration);
  int score() const;
  int getSize() const;

private:
  bool checkRectangleCollisions(SDL_FRect const &rectangle, std::vector<SDL_Rect> &other);
  template<typename RECTANGLE, typename OTHER>
  bool checkRectangleCollision(RECTANGLE const &rectangle, OTHER const &other);

  bool handlePacmanDotCollisions(Pacman const &pacman, std::vector<Dot> &dots);

  template <typename CHARACTER>
  void moveCharacter(CHARACTER &character);

  bool checkMoveInBounds(SDL_FRect rectangle);

  std::size_t screen_width_;
  std::size_t screen_height_;
  std::size_t grid_width_;
  std::size_t grid_height_;

  Pacman pacman_;
  std::vector<Dot> dots_;
  std::vector<Dot> pellets_;
  std::vector<SDL_Rect> walls_;
  std::vector<std::unique_ptr<Ghosts::Ghost>> ghosts_;



  int score_{0};
  static unsigned int constexpr time_between_title_update_{1000};
  // TODO: feels as if this is not the correct place to store this variable, maybe in main?
  static float constexpr pacman_speed = 2.0f;

  void update();
};
