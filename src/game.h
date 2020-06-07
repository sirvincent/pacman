#pragma once

#include "controller.h"
#include "renderer.h"
#include "dot.h"
#include "pacman.h"
#include "ghost.h"
#include "level.h"

#include "SDL.h"

#include <memory>
#include <filesystem>


class Game
{
public:
  Game(std::size_t screenWidth, std::size_t screenHeight, std::size_t gridWidth, std::size_t gridHeight, std::filesystem::path const executablePath);
  void run(Controller const &controller, Renderer &renderer, uint32_t const targetFrameDuration);
  int score() const;
  int getSize() const;

private:
  bool checkRectangleCollisions(SDL_FRect const &rectangle, std::vector<SDL_Rect> &other);
  template<typename RECTANGLE, typename OTHER>
  bool checkRectangleCollision(RECTANGLE const &rectangle, OTHER const &other);

  bool handlePacmanDotCollisions(Pacman const &pacman, std::vector<Dot> &dots);
  void handlePacmanGhostCollisions(Pacman const &pacman, std::vector<std::unique_ptr<Ghosts::Ghost>> &ghosts);

  template<typename CHARACTER>
  void moveCharacter(CHARACTER &character);

  bool checkMoveInBounds(SDL_FRect rectangle);

  void update(bool &running);

  std::size_t screenWidth_;
  std::size_t screenHeight_;
  std::size_t gridWidth_;
  std::size_t gridHeight_;

  Pacman pacman_;
  std::vector<Dot> dots_;
  std::vector<Dot> pellets_;
  std::vector<SDL_Rect> walls_;
  std::vector<std::unique_ptr<Ghosts::Ghost>> ghosts_;

  bool scaredGhosts_{false};
  std::chrono::time_point<std::chrono::system_clock> startScaredGhosts = std::chrono::system_clock::now();
  int const durationScaredGhosts_{10000};

  int score_{0};
  // TODO: do we want thi sto belong to the game or just make a global?
  std::filesystem::path const executablePath_;

  unsigned int const timeBetweenTitleUpdate_{1000};
};
