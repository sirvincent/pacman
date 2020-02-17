#pragma once

#include "movement.h"

#include "SDL.h"

#include <iostream>
#include <tuple>


namespace Ghosts
{

// TODO: I would like to make Ghost an abstract base class, however
//       it seems incorrect to make it abstract while it inherets from SDL_FRect
class Ghost : public SDL_FRect, public Movement
{
public:
  Ghost(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, float speed) :
    rgba_({red, green, blue, alpha}), Movement(speed, speed, speed, speed) {}

  void move()
  {
    x += velocity_x_;
    y += velocity_y_;
  }

  virtual void moveMethod() { std::cout << "ghost move method" << std::endl; };

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
  // TODO: should be const
  int score_{200};

  std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> rgba_{0xFF, 0xFF, 0xFF, 0xFF};
};

}
