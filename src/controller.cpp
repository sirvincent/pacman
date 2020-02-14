#include "controller.h"

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
    else if (event.type == SDL_KEYDOWN)
    {
      switch (event.key.keysym.sym)
      {
        case SDLK_UP:
          pacman.direction = Pacman::Direction::kUp;
          break;

        case SDLK_DOWN:
          pacman.direction = Pacman::Direction::kDown;
          break;

        case SDLK_LEFT:
          pacman.direction = Pacman::Direction::kLeft;
          break;

        case SDLK_RIGHT:
          pacman.direction = Pacman::Direction::kRight;
          break;
      }
    }
  }
}
