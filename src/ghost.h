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

  std::string onActiveSprite() override
  {
    std::string activeSpriteName{""};
    // TODO: repeating switch in derived Ghost, can we remove the repetition?
    switch (direction)
    {
      // TODO: it feels as if these magic numbers belong into some sort of configuration file
      //       which contains a connection to the specific sprite sheet in use
      // TODO: can we make the SDL_Rect constexpr? They will not change after compile time
      case Movement::Direction::up:
        activeSpriteName = "up";
        break;
      case Movement::Direction::down:
        activeSpriteName = "down";
        break;
      case Movement::Direction::left:
        activeSpriteName = "left";
        break;
      case Movement::Direction::right:
        activeSpriteName = "right";
        break;
      default:
        std::cout << "An unhandled direction is found" << std::endl;
        throw;
    }
    if (scared)
    {
      activeSpriteName += "_scared";
    }

    return activeSpriteName;
  }

  bool edible{false};
  bool scared{false};

  inline int score() const { return score_; }

private:
  int const score_{200};
};

}  // namespace Ghosts
