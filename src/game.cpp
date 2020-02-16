#include "game.h"

#include "SDL.h"

#include <iostream>
#include <cassert>


Game::Game(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height) :
  screen_width_(screen_width), screen_height_(screen_height), grid_width_(grid_width), grid_height_(grid_height),
  pacman_(grid_width, grid_height)
{
  Level level(screen_width, screen_height, grid_width, grid_height);
  level.load();
  // TODO: this smells
  dots_     = std::move(level.dots_);
  pellets_  = std::move(level.pellets_);
  walls_    = std::move(level.walls_);
  ghosts_   = std::move(level.ghosts_);
  pacman_.x = level.player_.x;
  pacman_.y = level.player_.y;
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

    renderer.render(pacman_, dots_, pellets_, walls_, ghosts_);


    // TODO: enforce frame duration, move into separate function
    uint32_t frame_end = SDL_GetTicks();

    frame_count++;
    uint32_t frame_duration = frame_end - frame_start;

    if (frame_end - title_timestamp >= time_between_title_update_) {
      renderer.updateWindowTitle(score_, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}


bool Game::checkRectangleCollision(SDL_FRect const &rectangle, std::vector<SDL_Rect> &other)
{
  for (auto it = other.begin(); it != other.end(); ++it)
  {
    if (checkRectangleCollision(rectangle, *it))
    {
      return true;
    }
  }
  return false;
}

// TODO: come up with a better short name than other for other rectangle
bool Game::checkRectangleCollision(SDL_FRect const &rectangle, SDL_Rect const &other)
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

bool Game::handlePacmanDotCollisions(Pacman const &pacman, std::vector<Dot> &dots)
{
  for (auto it = dots.begin(); it != dots.end(); ++it)
  {
    // TODO: give Dot a member to rectanlge?
    SDL_Rect dot_rectangle;
    dot_rectangle.x = it->x();
    dot_rectangle.y = it->y();
    dot_rectangle.w = it->radius();
    dot_rectangle.h = it->radius();

    if (checkRectangleCollision(pacman, dot_rectangle))
    {
      score_ += it->score();
      dots.erase(it);
      return true;
    }
  }

  return false;
}

void Game::update() {
  if (!pacman_.alive())
  {
    return;
  }

  // Based on lazy foos tutorial logic is simpler if moving x and y separately not both
  pacman_.move_x();
  // TODO: is it Game task to manage if pacman moves out of screen? I think so since it knows about the screen
  if (pacman_.x < 0 || pacman_.x > (screen_width_ - pacman_.w) || checkRectangleCollision(pacman_, walls_))
  {
    pacman_.x -= pacman_.velocity_x;
  }

  pacman_.move_y();
  if (pacman_.y < 0 || pacman_.y > (screen_height_ - pacman_.h) || checkRectangleCollision(pacman_, walls_))
  {
    pacman_.y -= pacman_.velocity_y;
  }

  handlePacmanDotCollisions(pacman_, dots_);
  if (handlePacmanDotCollisions(pacman_, pellets_))
  {
    // TODO: ghosts get scared and edible
  }

  for (auto &ghost : ghosts_)
  {
    ghost->move();
  }
}

int Game::score() const
{
  return score_;
}
