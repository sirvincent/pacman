#pragma once

#include "ghost.h"

namespace Ghosts
{

class Clyde : public Ghost
{
public:
  Clyde(float width, float height, float speed);

  void move() override;

private:

};

}
