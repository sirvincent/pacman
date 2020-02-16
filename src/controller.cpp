#include "controller.h"

#include "SDL.h"

#include <iostream>


void Controller::handleInput(bool &running, Pacman &pacman) const
{
  SDL_Event event;
  // TODO: the movement stutters a bit!
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      running = false;
    }
    else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
      switch (event.key.keysym.sym)
      {
        case SDLK_UP:
          pacman.wanted_direction = Direction::up;
          break;

        case SDLK_DOWN:
          pacman.wanted_direction = Direction::down;
          break;

        case SDLK_LEFT:
          pacman.wanted_direction = Direction::left;
          break;

        case SDLK_RIGHT:
          pacman.wanted_direction = Direction::right;
          break;
      }
    }
  }
}
