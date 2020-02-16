#include "blinky.h"

#include <iostream>

namespace Ghosts {

Blinky::Blinky(float width, float height) : Ghost(0xCB, 0x43, 0x35, 0xFF)
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}

void Blinky::move()
{
  // TODO: blinky should shadow the player
  std::cout << "I am blinky" << std::endl;

}

}
