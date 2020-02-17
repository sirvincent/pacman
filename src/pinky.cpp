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


void Pinky::moveMethod()
{
  // TODO: pinky should be speedy
  // TODO: is it not expensive to repeat the following lines for each move?
  long time_passed_since_last_update = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_update_).count();
  if (time_passed_since_last_update > method_duration_)
  {
    std::random_device random;
    std::knuth_b generator(random());
    std::uniform_int_distribution<uint8_t> distribution(0, 3);

    wanted_direction = static_cast<Movement::Direction>(distribution(generator));
    last_update_ = std::chrono::system_clock::now();
  }
}

}
