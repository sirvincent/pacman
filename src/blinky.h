#pragma once

#include "ghost.h"

namespace Ghosts
{

class Blinky : public Ghost
{
public:
  Blinky(float width, float height);
  void move() override;

private:
};

}
