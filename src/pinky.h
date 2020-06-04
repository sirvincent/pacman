#pragma once

#include "ghost.h"
#include "sprite_graphics.h"

#include <random>
#include <chrono>


namespace Ghosts
{

class Pinky : public Ghost, public Implementation::SpriteGraphics
{
public:
  Pinky(float width, float height, float speed);

  void moveMethod() override;
  std::pair<SDL_Texture *, SDL_Rect> active_sprite() override;

private:
  std::chrono::time_point<std::chrono::system_clock> last_update_ = std::chrono::system_clock::now();
  double const method_duration_{400};

};

}

namespace Pinky
{
constexpr float speed{2.4f};
}
