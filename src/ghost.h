#pragma once

#include "movement.h"
#include "animation.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <tuple>
#include <chrono>


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
    , startScaredTime_(std::chrono::system_clock::now())
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

  void setScaredAndEdible();
  void handleScaredAndEdible();

  inline bool edible() const { return edible_; }
  inline int score() const { return score_; }

private:
  bool edible_{false};
  bool scared_{false};
  bool blink_{false};
  // TODO: what is better milliseconds in name or as comment behind declaration?
  unsigned int const scaredDuration_{8000}; // milliseconds
  unsigned int const scaredDurationBlinking_{2000}; // milliseconds
  std::chrono::time_point<std::chrono::system_clock> startScaredTime_ = std::chrono::system_clock::now();

  int const score_{200};
};

}  // namespace Ghosts
