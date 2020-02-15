#include "game.h"

#include "SDL.h"

#include <iostream>
#include <cassert>


Game::Game(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height) :
  screen_width_(screen_width), screen_height_(screen_height), grid_width_(grid_width), grid_height_(grid_height),
  level_(screen_width, screen_height, grid_width, grid_height),
  pacman_(grid_width, grid_height)
{
  // TODO: No need for level_ to be part of the object, it can be destructed after loading in
  level_.load();
  // TODO: this smells
  dots_  = std::move(level_.dots_);
  walls_ = std::move(level_.walls_);
  pacman_.x = level_.player_.x;
  pacman_.y = level_.player_.y;
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

    renderer.render(pacman_, dots_, walls_);


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

// TODO: come up with a better short name than other for other rectangle
bool Game::checkRectangleCollision(SDL_Rect const &rectangle, SDL_Rect const &other)
{
  int const left_rectangle   = rectangle.x;
  int const right_rectangle  = rectangle.x + rectangle.w;
  int const top_rectangle    = rectangle.y;
  int const bottom_rectangle = rectangle.y + rectangle.h;

  int const left_other   = other.x;
  int const right_other  = other.x + other.w;
  int const top_other    = other.y;
  int const bottom_other = other.y + other.h;

  // check collision based on separating axis
  if (bottom_rectangle <= top_other)
  {
    return false;
  }
  if (top_rectangle >= bottom_other)
  {
    return false;
  }
  if (right_rectangle <= left_other)
  {
    return false;
  }
  if (left_rectangle  >= right_other)
  {
    return false;
  }

  return true;
}

void Game::update() {
  if (!pacman_.alive())
  {
    return;
  }


  // Based on lazy foos tutorial logic is simpler if moving x and y separately not both
  pacman_.move_x();
  // TODO: is it Game task to manage if pacman moves out of screen? I think so since it knows about the screen
  if (pacman_.x < 0)
  {
    pacman_.x = 0;
  }
  else if (pacman_.x > (screen_width_ - pacman_.width))
  {
    pacman_.x = screen_width_ - pacman_.width;
  }

  pacman_.move_y();
  if (pacman_.y < 0)
  {
    pacman_.y = 0;
  }
  else if (pacman_.y > (screen_height_ - pacman_.height))
  {
    pacman_.y = screen_height_ - pacman_.height;
  }

  // it should only be possible that pacman collides with 1 dot! not multiple, in case pacman moves along
  // the cells of the grid and not on the grid it will be fine else not.
  // hence currently it can fail due to that pacman is not precisely on the grid!
  for (auto it = dots_.begin(); it != dots_.end(); ++it)
  {
    // TODO: how to remove the boiler plate code from convert own objects to rectangle?
    //       Inherent from SDL_Rect?
    SDL_Rect pacman_rectangle;
    pacman_rectangle.x = pacman_.x;
    pacman_rectangle.y = pacman_.y;
    pacman_rectangle.w = pacman_.width;
    pacman_rectangle.h = pacman_.height;

    SDL_Rect dot_rectangle;
    dot_rectangle.x = it->x();
    dot_rectangle.y = it->y();
    dot_rectangle.w = it->radius();
    dot_rectangle.h = it->radius();

    if (checkRectangleCollision(pacman_rectangle, dot_rectangle))
    {
      dots_.erase(it);
      break;
    }

  }

  // Handle interaction pacman with environment, dots, walls or ghost
}

int Game::score() const
{
  return score_;
}
