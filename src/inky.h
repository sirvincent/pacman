#pragma once

#include "ghost.h"
#include "sprite_graphics.h"

#include <chrono>


namespace Ghosts {

class Inky : public Ghost
  , public Implementation::SpriteGraphics
{
public:
  Inky(float width, float height, float speed);

  void moveMethod() override;
  std::pair<SDL_Texture *, SDL_Rect> activeSprite() override;

private:
  std::chrono::time_point<std::chrono::system_clock> lastUpdate_ = std::chrono::system_clock::now();
  long const methodDuration_{400};
};

}  // namespace Ghosts

namespace Inky {
constexpr float speed{2.1f};
}
