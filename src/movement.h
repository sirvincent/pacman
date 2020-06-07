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

  Movement(float velocityX, float velocityY, float speed_x, float speed_y);

  void adjustXYVelocityOnDirection(Direction direction_to_go_to);

  float velocityX() const;
  float velocityY() const;

  // TODO: do we want getters/setters for these?
  Movement::Direction direction       = Movement::Direction::left;
  Movement::Direction wantedDirection = direction;

protected:
  float velocityX_;
  float velocityY_;

  float const speed_x_;
  float const speed_y_;

private:
};
