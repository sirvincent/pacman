#pragma once

#include "ghost.h"
#include "sprite_graphics.h"

#include <random>
#include <chrono>


namespace Ghosts {

class Blinky : public Ghost
  , public Implementation::SpriteGraphics
{
public:
  Blinky() = delete;
  Blinky(float width, float height, float speed);

  void moveMethod() override;
  std::pair<SDL_Texture *, SDL_Rect> active_sprite() override;

private:
  std::chrono::time_point<std::chrono::system_clock> last_update_ = std::chrono::system_clock::now();
  double const method_duration_{400};
};

}  // namespace Ghosts

namespace Blinky {
constexpr float speed{2.1f};
}
