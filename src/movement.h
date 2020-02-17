#pragma once


class Movement
{
public:
  enum class Direction
  {
    up,
    down,
    left,
    right
  };

  Movement(float velocity_x, float velocity_y, float speed_x, float speed_y);

  // TODO: implement a pure virtual move meant to be overwritten? But requires knowledge of x/y which Movement does not need

  void adjust_x_y_velocity_on_direction(Direction direction_to_go_to);

  float velocity_x() const;
  float velocity_y() const;

  // TODO: do we want getters/setters for these?
  Movement::Direction direction = Movement::Direction::left;
  Movement::Direction wanted_direction = direction;

protected:
  float velocity_x_;
  float velocity_y_;

  float const speed_x_;
  float const speed_y_;

private:

};
