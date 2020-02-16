#pragma once

#include "SDL.h"


// TODO: I would like to make Ghost an abstract base class, however
//       it seems incorrect to make it abstract while it inherets from SDL_FRect
class Ghost : public SDL_FRect
{
public:
  virtual void move() {}
  bool edible() const;
  bool scared() const;

private:
  // TODO: should be based on pacman.velocity, should be slightly bit faster
  float velocity{2.1f};

  bool edible_{false};
  bool scared_{false};
};
