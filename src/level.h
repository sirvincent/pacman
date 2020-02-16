#pragma once

#include "dot.h"

#include "SDL.h"

#include <vector>
#include <iostream>
#include <string>
#include <filesystem>


class Level {
public:
  Level(std::size_t const screen_width, std::size_t const screen_height, std::size_t const grid_width, std::size_t const grid_height);

  std::vector<Dot> dots_;
  std::vector<Dot> pellets_;
  std::vector<SDL_Rect> walls_;
  SDL_Point player_ = {-1, -1};

  void convertCharacterToGameObject(char const character, unsigned int x, unsigned int y);
  void load(std::string directory = "levels", std::string filename = "default");

private:
  std::size_t const screen_width_;
  std::size_t const screen_height_;
  std::size_t const grid_width_;
  std::size_t const grid_height_;
  // TODO: should this be part of Level or Game?
  static int constexpr pellet_score{50};


};
