#pragma once

#include "movement.h"
#include "animation.h"

#include <SDL2/SDL.h>

#include <vector>
#include <string>
#include <map>
#include <filesystem>
#include <utility>


class Pacman : public SDL_FRect
  , public Movement
  , public Implementation::Animation
{
public:
  Pacman(float width, float height);

  void move();

  bool alive() const;
  void alive(bool alive);

  std::string onActiveSprite() override;

private:
  bool alive_{true};

  uint32_t current_ms_since_start_;
  uint32_t const duration_between_animation_ms_{200};
};


namespace Data {
namespace Pacman {
  // TODO: will be nice if this is constexpr
  static std::map<std::string, AnimationProperty> const animations = {
    {"up", AnimationProperty({SDL_Rect{556, 853, 138, 170}}, 100)},
    {"down", AnimationProperty({SDL_Rect{556, 5, 138, 170}}, 100)},
    {"left", AnimationProperty({SDL_Rect{556, 342, 138, 170}, SDL_Rect{556, 508, 138, 170}}, 100)},
    {"right", AnimationProperty({SDL_Rect{556, 172, 138, 170}, SDL_Rect{556, 674, 138, 170}}, 100)}};

  float constexpr speed = 2.0f;
}  // namespace Pacman
}  // namespace Data
