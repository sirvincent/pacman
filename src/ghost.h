#pragma once

#include "SDL.h"

#include <iostream>
#include <tuple>


namespace Ghosts
{

enum class Direction : uint8_t
{
  up,
  down,
  left,
  right
};

// TODO: I would like to make Ghost an abstract base class, however
//       it seems incorrect to make it abstract while it inherets from SDL_FRect
class Ghost : public SDL_FRect
{
public:
  Ghost(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
    rgba_({red, green, blue, alpha}) {}

  virtual void move() { std::cout << "ghost" << std::endl; }
  inline bool edible() const { return edible_; }
  inline bool scared() const { return scared_; }
  inline int score() const { return score_; }
  inline std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> rgba() const { return rgba_; }

protected:
  // TODO: should be based on pacman.velocity, should be slightly bit faster
  float velocity_{2.1f};
  float velocity_x_ = velocity_;
  float velocity_y_ = velocity_;

  bool edible_{false};
  bool scared_{false};

private:
  // TODO: should be const
  int score_{200};

  std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> rgba_{0xFF, 0xFF, 0xFF, 0xFF};
};

}
