#pragma once

#include "movement.h"
#include "sprite_graphics.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <tuple>


namespace Ghosts {

// TODO: ghost is a mix of implementation and interface inheretance, refactor according to C.129
class Ghost : public SDL_FRect
  , public Movement
  , public virtual SpriteGraphics
{
public:
  Ghost(float speed) : Movement(speed, speed, speed, speed) {}
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

  // TODO: build in assumption is that every derived ghost scared sprite is at the same location
  //       on the sprite sheet!
  SDL_Rect handleSpriteScared(Movement::Direction const &movement_direction)
  {
    switch (movement_direction)
    {
      // TODO: adjusted values
      case Movement::Direction::up:
        return SDL_Rect{130, 850, 115, 165};
        break;
      case Movement::Direction::down:
        return SDL_Rect{0, 850, 115, 165};
        break;
      case Movement::Direction::left:
        return SDL_Rect{275, 850, 115, 165};
        break;
      case Movement::Direction::right:
        return SDL_Rect{410, 850, 115, 165};
        break;
      default:
        std::cout << "An unhandled direction is found" << std::endl;
        throw;
    }
  }

  bool edible{false};
  bool scared{false};

  inline int score() const { return score_; }

private:
  int const score_{200};
};

}  // namespace Ghosts
