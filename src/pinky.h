#pragma once

#include "ghost.h"
#include "sprite_graphics.h"

#include <random>
#include <chrono>


namespace Ghosts {

class Pinky : public Ghost
  , public Implementation::SpriteGraphics
{
public:
  Pinky(float width, float height, float speed);

  void moveMethod() override;
  std::pair<SDL_Texture *, SDL_Rect> activeSprite() override;

private:
  std::chrono::time_point<std::chrono::system_clock> lastUpdate_ = std::chrono::system_clock::now();
  double const methodDuration_{400};
};

}  // namespace Ghosts

namespace Pinky {
constexpr float speed{2.4f};
}
