#pragma once

#include "ghost.h"

#include <chrono>


namespace Ghosts {

class Inky : public Ghost
{
public:
  Inky(float width, float height);

  void moveMethod() override;

private:
  std::chrono::time_point<std::chrono::system_clock> lastUpdate_ = std::chrono::system_clock::now();
  long const methodDuration_{400};
};

}  // namespace Ghosts


namespace Data {
namespace Inky {
  // TODO: will be nice if this is constexpr
  static std::map<std::string, AnimationProperty> const animations = {
    {"up",           AnimationProperty({SDL_Rect{130, 335, 115, 165}}, 100)},
    {"down",         AnimationProperty({SDL_Rect{0, 335, 115, 165}}, 100)},
    {"left",         AnimationProperty({SDL_Rect{275, 335, 115, 165}}, 100)},
    {"right",        AnimationProperty({SDL_Rect{410, 335, 115, 165}}, 100)},
    {"up_scared",    AnimationProperty({SDL_Rect{130, 850, 115, 165}}, 100)},
    {"down_scared",  AnimationProperty({SDL_Rect{0, 850, 115, 165}}, 100)},
    {"left_scared",  AnimationProperty({SDL_Rect{275, 850, 115, 165}}, 100)},
    {"right_scared", AnimationProperty({SDL_Rect{410, 850, 115, 165}}, 100)}
  };

  constexpr float speed{2.1f};
}  // namespace Inky
}  // namespace Data
