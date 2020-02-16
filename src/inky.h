#pragma once

#include "ghost.h"

namespace Ghosts
{

class Inky : public Ghost
{
public:
  Inky(float width, float height);

  void move() override;

private:

};

}
