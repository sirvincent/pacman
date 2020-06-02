#pragma once

#include "movement.h"

#include "SDL.h"

#include <vector>
#include <string>
#include <map>
#include <filesystem>
#include <utility>


class Pacman : public SDL_FRect, public Movement
{
public:
  Pacman(float width, float height, float speed);

  void move();

  bool alive() const;
  void alive(bool alive);

  void initialize_texture(SDL_Renderer *sdl_renderer_, std::filesystem::path const &executable_path);
  std::pair<SDL_Texture *, SDL_Rect> active_sprite();

  static float constexpr pacman_speed = 2.0f;

private:
  void construct_movement_sprite_sheet_rectangles();
  // sprite_sheet is owned by renderer, not by pacman this is not insightfull but is required
  // since it is rendered in a hardware optimized way, so the hardware owns it (renderer)
  SDL_Texture *sprite_sheet_;
  bool alive_{true};

};


