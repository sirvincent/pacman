#include "inky.h"

#include <iostream>
#include <random>


namespace Ghosts {

Inky::Inky(float width, float height) :
    Ghost(Data::Inky::speed, "pac-classic/pac-classic_c-toy.png", Data::Inky::animations, "left")
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}


void Inky::moveMethod()
{
  // TODO: inky should be bashfull
  long timePassedSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate_).count();
  if (timePassedSinceLastUpdate > methodDuration_)
  {
    std::random_device random;
    std::ranlux48 generator(random());
    std::uniform_int_distribution<uint8_t> distribution(0, 3);

    wantedDirection = static_cast<Movement::Direction>(distribution(generator));
    lastUpdate_     = std::chrono::system_clock::now();
  }
}

}  // namespace Ghosts
