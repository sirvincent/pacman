#include "clyde.h"

#include <iostream>
#include <random>


namespace Ghosts {

Clyde::Clyde(float width, float height, float speed) : Ghost(speed),
  Implementation::SpriteGraphics("pac-classic/pac-classic_c-toy.png")
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}


void Clyde::moveMethod()
{
  // TODO: clyde should be pokey
  long time_passed_since_last_update = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_update_).count();
  if (time_passed_since_last_update > method_duration_)
  {
    std::random_device random;
    std::minstd_rand generator(random());
    std::uniform_int_distribution<uint8_t> distribution(0, 3);

    wanted_direction = static_cast<Movement::Direction>(distribution(generator));
    last_update_ = std::chrono::system_clock::now();
  }
}

std::pair<SDL_Texture *, SDL_Rect> Clyde::active_sprite()
{
  switch (direction)
  {
    case Movement::Direction::up:
      return std::make_pair(sprite_sheet_, SDL_Rect{130, 500, 115, 165});
      break;
    case Movement::Direction::down:
      return std::make_pair(sprite_sheet_, SDL_Rect{0, 500, 115, 165});
      break;
    case Movement::Direction::left:
      return std::make_pair(sprite_sheet_, SDL_Rect{275, 500, 115, 165});
      break;
    case Movement::Direction::right:
      return std::make_pair(sprite_sheet_, SDL_Rect{410, 500, 115, 165});
      break;
  }
}

}
