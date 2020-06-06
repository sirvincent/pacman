#pragma once

#include "movement.h"
#include "sprite_graphics.h"

#include "SDL.h"

#include <iostream>
#include <tuple>


namespace Ghosts
{

class Ghost : public SDL_FRect, public Movement, public virtual SpriteGraphics
{
public:
  Ghost(float speed) : Movement(speed, speed, speed, speed) {}
  // from: https://en.cppreference.com/w/cpp/language/destructor
  // "Deleting an object through pointer to base invokes undefined behavior unless the destructor in the base class is virtual"
  // Destructor of derived Ghost e.g. Blinky is then not called
  virtual ~Ghost() = default;

  void move()
  {
    x += velocity_x_;
    y += velocity_y_;
  }

  virtual void moveMethod()  = 0;

  inline bool edible() const { return edible_; }
  inline void edible(bool const edible) { /* TODO: change sprite to scared */ edible_ = edible; }

  inline bool scared() const { return scared_; }
  inline void scared(bool const scared) { /* TODO: change sprite to scared */ scared_ = scared; }

  inline int score() const { return score_; }

protected:
  bool edible_{false};
  bool scared_{false};

private:
  int const score_{200};
};

}
