#include "movement.h"


Movement::Movement(float velocity_x, float velocity_y, float speed_x, float speed_y) : velocity_x_(velocity_x), velocity_y_(velocity_y), speed_x_(speed_x), speed_y_(speed_y) {}


float Movement::velocity_x() const
{
  return velocity_x_;
}
float Movement::velocity_y() const
{
  return velocity_y_;
}

void Movement::adjust_x_y_velocity_on_direction(Direction direction_to_go_to)
{
  switch (direction_to_go_to)
  {
    case Direction::up:
      velocity_y_ = -speed_y_;
      velocity_x_ = 0;
      break;
    case Direction::down:
      velocity_y_ = speed_y_;
      velocity_x_ = 0;
      break;
    case Direction::left:
      velocity_y_ = 0;
      velocity_x_ = -speed_x_;
      break;
    case Direction::right:
      velocity_y_ = 0;
      velocity_x_ = speed_x_;
      break;
  }
}
