#include "blinky.h"

#include <iostream>


namespace Ghosts {

Blinky::Blinky(float width, float height, float speed) : Ghost(speed),
  Implementation::SpriteGraphics("pac-classic/pac-classic_c-toy.png")
{
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}

void Blinky::moveMethod()
{
  // TODO: blinky should shadow the player
  //       use A* for this
  long time_passed_since_last_update = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_update_).count();
  if (time_passed_since_last_update > method_duration_)
  {
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution<uint8_t> distribution(0, 3);

    wanted_direction = static_cast<Movement::Direction>(distribution(generator));
    last_update_ = std::chrono::system_clock::now();
  }
}

std::pair<SDL_Texture *, SDL_Rect> Blinky::active_sprite()
{
  switch (direction)
  {
    case Movement::Direction::up:
      return std::make_pair(sprite_sheet_, SDL_Rect{130, 0, 115, 165});
      break;
    case Movement::Direction::down:
      return std::make_pair(sprite_sheet_, SDL_Rect{0, 0, 115, 165});
      break;
    case Movement::Direction::left:
      return std::make_pair(sprite_sheet_, SDL_Rect{275, 0, 115, 165});
      break;
    case Movement::Direction::right:
      return std::make_pair(sprite_sheet_, SDL_Rect{410, 0, 115, 165});
      break;
  }
}

}
