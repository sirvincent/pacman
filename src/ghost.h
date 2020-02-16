#pragma once

#include "SDL.h"

#include <iostream>

namespace Ghosts
{

// TODO: I would like to make Ghost an abstract base class, however
//       it seems incorrect to make it abstract while it inherets from SDL_FRect
class Ghost : public SDL_FRect
{
public:
  virtual void move() { std::cout << "ghost" << std::endl; }
  inline bool edible() const { return edible_; }
  inline bool scared() const { return scared_; }
  inline int score() const { return score_; }

private:
  // TODO: should be based on pacman.velocity, should be slightly bit faster
  float velocity{2.1f};

  bool edible_{false};
  bool scared_{false};
  int score_{200};
};

}
