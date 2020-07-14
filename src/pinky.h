#pragma once

#include "ghost.h"

#include <random>
#include <chrono>


namespace Ghosts {

class Pinky : public Ghost
{
public:
  Pinky(float width, float height);

  void moveMethod() override;

private:
  std::chrono::time_point<std::chrono::system_clock> lastUpdate_ = std::chrono::system_clock::now();
  long const methodDuration_{400};
};

}  // namespace Ghosts


namespace Data {
namespace Pinky {
  // TODO: will be nice if this is constexpr
  static std::map<std::string, AnimationProperty> const animations = {
    {"up", AnimationProperty({SDL_Rect{130, 165, 115, 165}}, 100)},
    {"down", AnimationProperty({SDL_Rect{0, 165, 115, 165}}, 100)},
    {"left", AnimationProperty({SDL_Rect{275, 165, 115, 165}}, 100)},
    {"right", AnimationProperty({SDL_Rect{410, 165, 115, 165}}, 100)},
    {"up_scared", AnimationProperty({SDL_Rect{130, 850, 115, 165}}, 100)},
    {"down_scared", AnimationProperty({SDL_Rect{0, 850, 115, 165}}, 100)},
    {"left_scared", AnimationProperty({SDL_Rect{275, 850, 115, 165}}, 100)},
    {"right_scared", AnimationProperty({SDL_Rect{410, 850, 115, 165}}, 100)},
    {"up_scared_blinking", AnimationProperty({SDL_Rect{130, 850, 115, 165}, SDL_Rect{130, 675, 115, 165}}, 100)},
    {"down_scared_blinking", AnimationProperty({SDL_Rect{0, 850, 115, 165}, SDL_Rect{130, 675, 115, 165}}, 100)},
    {"left_scared_blinking", AnimationProperty({SDL_Rect{275, 850, 115, 165}, SDL_Rect{130, 675, 115, 165}}, 100)},
    {"right_scared_blinking", AnimationProperty({SDL_Rect{410, 850, 115, 165}, SDL_Rect{130, 675, 115, 165}}, 100)}};

  constexpr float speed{2.4f};
}  // namespace Pinky
}  // namespace Data
