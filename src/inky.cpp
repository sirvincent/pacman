#include "inky.h"

#include <iostream>


namespace Ghosts {

Inky::Inky(float width, float height) : Ghost(0x00, 0xF3, 0xFF, 0xFF)
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}

void Inky::move()
{
  // TODO: inky should be bashfull
  std::cout << "I am inky" << std::endl;

}

}
