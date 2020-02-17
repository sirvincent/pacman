#pragma once

#include "movement.h"

#include "SDL.h"

#include <iostream>
#include <tuple>


namespace Ghosts
{

// Ghost was intended to be an abstract base class, but since we have a ghosts vector where we use
// base ptr to derived objects this is not possible. I like the vector circumvents calling the 4 ghosts separately.
class Ghost : public SDL_FRect, public Movement
{
public:
  Ghost(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, float speed) :
    Movement(speed, speed, speed, speed), rgba_({red, green, blue, alpha}){}

  void move()
  {
    x += velocity_x_;
    y += velocity_y_;
  }

  virtual void moveMethod() { std::cout << "ghost move method" << std::endl; }

  inline bool edible() const { return edible_; }
  inline void edible(bool const edible) { /* TODO: change sprite to scared */ edible_ = edible; }

  inline bool scared() const { return scared_; }
  inline void scared(bool const scared) { /* TODO: change sprite to scared */ scared_ = scared; }

  inline int score() const { return score_; }

  inline std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> rgba() const { return rgba_; }

protected:
  bool edible_{false};
  bool scared_{false};

private:
  int const score_{200};

  std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> rgba_{0xFF, 0xFF, 0xFF, 0xFF};
};

}
