#include "movement.h"


Movement::Movement(float velocityX, float velocityY, float speed_x, float speed_y) : velocityX_(velocityX), velocityY_(velocityY), speed_x_(speed_x), speed_y_(speed_y) {}


float Movement::velocityX() const
{
  return velocityX_;
}
float Movement::velocityY() const
{
  return velocityY_;
}

void Movement::adjustXYVelocityOnDirection(Direction direction_to_go_to)
{
  switch (direction_to_go_to)
  {
    case Direction::up:
      velocityY_ = -speed_y_;
      velocityX_ = 0;
      break;
    case Direction::down:
      velocityY_ = speed_y_;
      velocityX_ = 0;
      break;
    case Direction::left:
      velocityY_ = 0;
      velocityX_ = -speed_x_;
      break;
    case Direction::right:
      velocityY_ = 0;
      velocityX_ = speed_x_;
      break;
  }
}
