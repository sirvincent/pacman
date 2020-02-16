#include "clyde.h"

#include <iostream>


namespace Ghosts {

Clyde::Clyde(float width, float height) : Ghost(0xF3, 0x9C, 0x12, 0xFF)
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}

void Clyde::move()
{
  // TODO: clyde should be pokey
  std::cout << "I am clyde" << std::endl;

}

}
