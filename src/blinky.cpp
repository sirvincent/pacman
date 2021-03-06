#include "blinky.h"

#include <iostream>


namespace Ghosts {

Blinky::Blinky(float width, float height)
  : Ghost(Data::Blinky::speed, "pac-classic/pac-classic_c-toy.png", Data::Blinky::animations, "left")
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}

void Blinky::moveMethod()
{
  // TODO: blinky should shadow the player
  //       use A* for this
  long timePassedSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate_).count();
  if (timePassedSinceLastUpdate > methodDuration_)
  {
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution<uint8_t> distribution(0, 3);

    wantedDirection = static_cast<Movement::Direction>(distribution(generator));
    lastUpdate_     = std::chrono::system_clock::now();
  }
}

}  // namespace Ghosts
