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
          pacman.velocity_y -= pacman.velocity;
          break;

        case SDLK_DOWN:
          pacman.velocity_y += pacman.velocity;
          break;

        case SDLK_LEFT:
          pacman.velocity_x -= pacman.velocity;
          break;

        case SDLK_RIGHT:
          pacman.velocity_x += pacman.velocity;
          break;
      }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
      // TODO: change to an if it will not be extended, I find that clearer
      switch (event.key.keysym.sym)
      {
        case SDLK_UP:
          pacman.velocity_y += pacman.velocity;
          break;
        case SDLK_DOWN:
          pacman.velocity_y -= pacman.velocity;
          break;
        case SDLK_LEFT:
          pacman.velocity_x += pacman.velocity;
          break;
        case SDLK_RIGHT:
          pacman.velocity_x -= pacman.velocity;
          break;
      }
    }
  }
}
