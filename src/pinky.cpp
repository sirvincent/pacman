#include "pinky.h"

#include <iostream>


namespace Ghosts {

Pinky::Pinky(float width, float height, float speed) : Ghost(0xFD, 0x67, 0xFF, 0xFF, speed)
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}

void Pinky::move()
{
  // TODO: pinky should be speedy
}

}
