#include "inky.h"

#include <iostream>


namespace Ghosts {

Inky::Inky(float width, float height, float speed) : Ghost(0x00, 0xF3, 0xFF, 0xFF, speed)
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}

void Inky::move()
{
  // TODO: inky should be bashfull

}

}
