#pragma once

#include "SDL.h"

#include <utility>


// a pure virtual interface class, following Core Guidelines C.129 design class hierarchy
class SpriteGraphics
{
public:
  virtual std::pair<SDL_Texture *, SDL_Rect> active_sprite() = 0;

private:

};
