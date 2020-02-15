#include "game.h"

#include "SDL.h"

#include <iostream>


Game::Game(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height) :
  pacman_(screen_width / grid_width, screen_height / grid_height)
{
  // TODO: dots is placed on stock but do we want it on the heap?
  unsigned int radius = grid_width / 2;
  dots_.push_back(Dot(screen_width / 2  + grid_width  / 2 - radius / 2,
                      screen_height / 2 + grid_height / 2 - radius / 2,
                      radius));
}


void Game::run(Controller const &controller, Renderer &renderer,
               uint32_t const target_frame_duration) {
  uint32_t title_timestamp = SDL_GetTicks();
  int frame_count = 0;
  bool running = true;

  while (running) {
    uint32_t frame_start = SDL_GetTicks();

    controller.handleInput(running, pacman_);

    update();

    renderer.render(pacman_, dots_);


    // TODO: enforce frame duration, move into separate function
    uint32_t frame_end = SDL_GetTicks();

    frame_count++;
    uint32_t frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.updateWindowTitle(score_, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::update() {
  if (!pacman_.alive())
  {
    return;
  }

  pacman_.update();

  // Handle interaction pacman with environment, dots, walls or ghost
}

int Game::score() const
{
  return score_;
}
