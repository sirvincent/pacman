#pragma once

#include "ghost.h"

#include <random>


namespace Ghosts
{

class Blinky : public Ghost
{
public:
  Blinky() = delete;
  Blinky(float width, float height);
  void move() override;

private:

};

}
