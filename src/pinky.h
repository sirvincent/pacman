#pragma once

#include "ghost.h"

namespace Ghosts
{

class Pinky : public Ghost
{
public:
  Pinky(float width, float height, float speed);

  void move() override;

private:

};

}
