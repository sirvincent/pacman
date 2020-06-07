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
  SDL_Rect sprite_sheet_rectangle;
  if (scared)
  {
    sprite_sheet_rectangle = handle_sprite_scared(direction);
  }
  else
  {
    // TODO: repeating switch in derived Ghost, can we remove the repetition?
    switch (direction)
    {
      // TODO: it feels as if these magic numbers belong into some sort of configuration file
      //       which contains a connection to the specific sprite sheet in use
      // TODO: can we make the SDL_Rect constexpr? They will not change after compile time
      case Movement::Direction::up:
        sprite_sheet_rectangle = {130, 500, 115, 165};
        break;
      case Movement::Direction::down:
        sprite_sheet_rectangle = {0, 500, 115, 165};
        break;
      case Movement::Direction::left:
        sprite_sheet_rectangle = {275, 500, 115, 165};
        break;
      case Movement::Direction::right:
        sprite_sheet_rectangle = {410, 500, 115, 165};
        break;
      default:
        std::cout << "An unhandled direction is found" << std::endl;
        throw;
    }
  }
  return std::make_pair(sprite_sheet_, sprite_sheet_rectangle);
}

}
