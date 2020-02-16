#include "clyde.h"

#include <iostream>


namespace Ghosts {

Clyde::Clyde(float width, float height, float speed) : Ghost(0xF3, 0x9C, 0x12, 0xFF, speed)
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}

void Clyde::move()
{
  // TODO: clyde should be pokey

}

}
