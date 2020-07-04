#include "clyde.h"

#include <iostream>
#include <random>


namespace Ghosts {

Clyde::Clyde(float width, float height) :
    Ghost(Data::Clyde::speed, "pac-classic/pac-classic_c-toy.png", Data::Clyde::animations, "left")
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}


void Clyde::moveMethod()
{
  // TODO: clyde should be pokey
  long timePassedSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate_).count();
  if (timePassedSinceLastUpdate > methodDuration_)
  {
    std::random_device random;
    std::minstd_rand generator(random());
    std::uniform_int_distribution<uint8_t> distribution(0, 3);

    wantedDirection = static_cast<Movement::Direction>(distribution(generator));
    lastUpdate_     = std::chrono::system_clock::now();
  }
}

}  // namespace Ghosts
