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
  void handlePacmanGhostCollisions(Pacman const &pacman, std::vector<std::unique_ptr<Ghosts::Ghost>> &ghosts);

  template <typename CHARACTER>
  void moveCharacter(CHARACTER &character);

  bool checkMoveInBounds(SDL_FRect rectangle);

  void update(bool &running);

  std::size_t screen_width_;
  std::size_t screen_height_;
  std::size_t grid_width_;
  std::size_t grid_height_;

  Pacman pacman_;
  std::vector<Dot> dots_;
  std::vector<Dot> pellets_;
  std::vector<SDL_Rect> walls_;
  std::vector<std::unique_ptr<Ghosts::Ghost>> ghosts_;

  bool scared_ghosts_{false};
  std::chrono::time_point<std::chrono::system_clock> start_scared_ghosts_ = std::chrono::system_clock::now();
  int const duration_scared_ghosts_{10000};

  int score_{0};

  unsigned int const time_between_title_update_{1000};
};
