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
    else if (event.type == SDL_KEYDOWN)
    {
      switch (event.key.keysym.sym)
      {
        case SDLK_UP:
          pacman.direction = Pacman::Direction::up;
          break;

        case SDLK_DOWN:
          pacman.direction = Pacman::Direction::down;
          break;

        case SDLK_LEFT:
          pacman.direction = Pacman::Direction::left;
          break;

        case SDLK_RIGHT:
          pacman.direction = Pacman::Direction::right;
          break;
      }
    }
    else if (event.type == SDL_KEYUP)
    {
      // TODO: change to an if it will not be extended, I find that clearer
      switch (event.key.keysym.sym)
      {
        case SDLK_UP:
          [[fallthrough]];
        case SDLK_DOWN:
          [[fallthrough]];
        case SDLK_LEFT:
          [[fallthrough]];
        case SDLK_RIGHT:
          pacman.direction = Pacman::Direction::none;
          break;
      }
    }
  }
}
