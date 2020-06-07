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
  long timePassedSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate_).count();
  if (timePassedSinceLastUpdate > methodDuration_)
  {
    std::random_device random;
    std::minstd_rand generator(random());
    std::uniform_int_distribution<uint8_t> distribution(0, 3);

    wantedDirection = static_cast<Movement::Direction>(distribution(generator));
    lastUpdate_     = std::chrono::system_clock::now();
  }
}


std::pair<SDL_Texture *, SDL_Rect> Clyde::activeSprite()
{
  SDL_Rect spriteSheetRectangle;
  if (scared)
  {
    spriteSheetRectangle = handleSpriteScared(direction);
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
        spriteSheetRectangle = {130, 500, 115, 165};
        break;
      case Movement::Direction::down:
        spriteSheetRectangle = {0, 500, 115, 165};
        break;
      case Movement::Direction::left:
        spriteSheetRectangle = {275, 500, 115, 165};
        break;
      case Movement::Direction::right:
        spriteSheetRectangle = {410, 500, 115, 165};
        break;
      default:
        std::cout << "An unhandled direction is found" << std::endl;
        throw;
    }
  }
  return std::make_pair(spriteSheet_, spriteSheetRectangle);
}

}  // namespace Ghosts
