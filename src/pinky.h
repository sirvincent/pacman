#pragma once

#include "ghost.h"

#include <random>
#include <chrono>


namespace Ghosts
{

class Pinky : public Ghost
{
public:
  Pinky(float width, float height, float speed);

  void move() override;
  void moveMethod() override;

private:
  std::chrono::time_point<std::chrono::system_clock> last_update_ = std::chrono::system_clock::now();
  double const method_duration_{400};

};

}
