#pragma once

#include "ghost.h"

#include <chrono>


namespace Ghosts
{

class Inky : public Ghost
{
public:
  Inky(float width, float height, float speed);

  void moveMethod() override;

private:
  std::chrono::time_point<std::chrono::system_clock> last_update_ = std::chrono::system_clock::now();
  double const method_duration_{400};

};

}

namespace Inky
{
constexpr float speed{2.1f};
}
