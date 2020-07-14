#include "pinky.h"

#include <iostream>


namespace Ghosts {

Pinky::Pinky(float width, float height)
  : Ghost(Data::Pinky::speed, "pac-classic/pac-classic_c-toy.png", Data::Pinky::animations, "left")
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}


void Pinky::moveMethod()
{
  // TODO: pinky should be speedy
  long timePassedSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate_).count();
  if (timePassedSinceLastUpdate > methodDuration_)
  {
    std::random_device random;
    std::knuth_b generator(random());
    std::uniform_int_distribution<uint8_t> distribution(0, 3);

    wantedDirection = static_cast<Movement::Direction>(distribution(generator));
    lastUpdate_     = std::chrono::system_clock::now();
  }
}

}  // namespace Ghosts
