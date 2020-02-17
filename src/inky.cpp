#include "inky.h"

#include <iostream>
#include <random>


namespace Ghosts {

Inky::Inky(float width, float height, float speed) : Ghost(0x00, 0xF3, 0xFF, 0xFF, speed)
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}


void Inky::moveMethod()
{
  // TODO: is it not expensive to repeat the following lines for each move?
  long time_passed_since_last_update = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_update_).count();
  if (time_passed_since_last_update > method_duration_)
  {
    std::random_device random;
    std::ranlux48 generator(random());
    std::uniform_int_distribution<uint8_t> distribution(0, 3);

    wanted_direction = static_cast<Movement::Direction>(distribution(generator));
    last_update_ = std::chrono::system_clock::now();
  }
}


void Inky::move()
{
  // TODO: inky should be bashfull

  x += velocity_x_;
  y += velocity_y_;

}

}
