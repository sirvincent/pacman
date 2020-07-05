#pragma once

#include "movement.h"
#include "animation.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <tuple>


namespace Ghosts {

// TODO: ghost is a mix of implementation and interface inheretance, refactor according to C.129
class Ghost : public SDL_FRect
  , public Movement
  , public Implementation::Animation
{
public:
  Ghost(float speed, std::string relativePathSpriteSheetToAssetsDirectory, std::map<std::string, AnimationProperty> animations, std::string spriteStartName)
    : Movement(speed, speed, speed, speed)
    , Implementation::Animation(relativePathSpriteSheetToAssetsDirectory, SDL_GetTicks(), animations, spriteStartName)
  {}
  // from: https://en.cppreference.com/w/cpp/language/destructor
  // "Deleting an object through pointer to base invokes undefined behavior unless the destructor in the base class is virtual"
  // Destructor of derived Ghost e.g. Blinky is then not called
  virtual ~Ghost() = default;

  void move()
  {
    x += velocityX_;
    y += velocityY_;
  }

  virtual void moveMethod() = 0;

  std::string onActiveSprite() override;

  bool edible{false};
  bool scared{false};

  inline int score() const { return score_; }

private:
  // TODO: what is better milliseconds in name or as comment behind declaration?
  unsigned int const scaredDuration_{10000}; // milliseconds
  unsigned int const scaredBlinking_{2000}; // milliseconds
  int const score_{200};
};

}  // namespace Ghosts
