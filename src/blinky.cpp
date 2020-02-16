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

  // TODO: is it not expensive to repeat the following lines for each move?
  std::random_device random;
  std::mt19937 generator(random());
  std::uniform_int_distribution<uint8_t> distribution(0, 3);

  // TODO: blinky should shadow the player
  //       use A* for this

  // TODO: returns an uint8_t and the enum class Direction underlying type is also uint8_t how
  //       to ensure?
  Ghosts::Direction direction = static_cast<Ghosts::Direction>(distribution(generator));
  std::cout << "I am blinky" << std::endl;
  std::cout << "moving: " << unsigned(direction) << std::endl;

  switch (direction)
  {
    case Ghosts::Direction::up:
      velocity_y_ = -velocity_;
      velocity_x_ = 0;
      break;
    case Ghosts::Direction::down:
      velocity_y_ = velocity_;
      velocity_x_ = 0;
      break;
    case Ghosts::Direction::left:
      velocity_y_ = 0;
      velocity_x_ = -velocity_;
      break;
    case Ghosts::Direction::right:
      velocity_y_ = 0;
      velocity_x_ = velocity_;
      break;
  }

  x += velocity_x_;
  y += velocity_y_;
}

}
