#pragma once

#include "movement.h"
#include "sprite_graphics.h"

#include "SDL.h"

#include <vector>
#include <string>
#include <map>
#include <filesystem>
#include <utility>


class Pacman : public SDL_FRect
  , public Movement
  , public Implementation::SpriteGraphics
{
public:
  Pacman(float width, float height, float speed);

  void move();

  bool alive() const;
  void alive(bool alive);

  std::pair<SDL_Texture *, SDL_Rect> activeSprite() override;

  static float constexpr pacman_speed = 2.0f;

private:
  bool alive_{true};
};
