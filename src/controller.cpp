#include "controller.h"
#include "movement.h"

#include "SDL.h"

#include <iostream>


void Controller::handleInput(bool &running, Pacman &pacman) const
{
  SDL_Event event;
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
          pacman.wantedDirection = Movement::Direction::up;
          break;

        case SDLK_DOWN:
          pacman.wantedDirection = Movement::Direction::down;
          break;

        case SDLK_LEFT:
          pacman.wantedDirection = Movement::Direction::left;
          break;

        case SDLK_RIGHT:
          pacman.wantedDirection = Movement::Direction::right;
          break;
        case SDLK_ESCAPE:
          running = false;
          break;
      }
    }
  }
}
