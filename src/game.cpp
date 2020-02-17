#include "game.h"

#include "SDL.h"

#include <iostream>
#include <cassert>


Game::Game(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height) :
  screen_width_(screen_width), screen_height_(screen_height), grid_width_(grid_width), grid_height_(grid_height),
  pacman_(grid_width, grid_height, pacman_speed)
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

    running = update();

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


bool Game::checkRectangleCollisions(SDL_FRect const &rectangle, std::vector<SDL_Rect> &other)
{
  for (auto it = other.begin(); it != other.end(); ++it)
  {
    if (checkRectangleCollision<SDL_FRect, SDL_Rect>(rectangle, *it))
    {
      return true;
    }
  }
  return false;
}

// TODO: come up with a better short name than other for other rectangle
template<typename RECTANGLE, typename OTHER>
bool Game::checkRectangleCollision(RECTANGLE const &rectangle, OTHER const &other)
{
  // TODO: I picked the largest type of SDL_FRect and SDL_Rect but is there a way to deduce
  //       this type from the object?
  float const left_rectangle   = rectangle.x;
  float const right_rectangle  = rectangle.x + rectangle.w;
  float const top_rectangle    = rectangle.y;
  float const bottom_rectangle = rectangle.y + rectangle.h;

  float const left_other   = other.x;
  float const right_other  = other.x + other.w;
  float const top_other    = other.y;
  float const bottom_other = other.y + other.h;

  // check if not colliding based on separating axis
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

    if (checkRectangleCollision<SDL_FRect, SDL_Rect>(pacman, dot_rectangle))
    {
      score_ += it->score();
      dots.erase(it);
      return true;
    }
  }

  return false;
}


// require CHARACTER is a SDL_Rect or SDL_FRect object
// require CHARACTER is a Movement object
template <typename CHARACTER>
void Game::moveCharacter(CHARACTER &character)
{
  character.adjust_x_y_velocity_on_direction(character.wanted_direction);
  CHARACTER wanted_pacman = character;
  wanted_pacman.x = character.x + character.velocity_x();
  wanted_pacman.y = character.y + character.velocity_y();

  bool valid_direction = checkMoveInBounds(wanted_pacman);

  if (!valid_direction)
  {
    character.adjust_x_y_velocity_on_direction(character.direction);
    CHARACTER wanted_pacman_old = character;
    wanted_pacman_old.x = character.x + character.velocity_x();
    wanted_pacman_old.y = character.y + character.velocity_y();

    bool valid_old_direction = checkMoveInBounds(wanted_pacman_old);
    if (valid_old_direction)
    {
      character.move();
    }
  }
  else
  {
    character.direction = character.wanted_direction;
    character.move();
  }
}


bool Game::checkMoveInBounds(SDL_FRect rectangle)
{
  if (rectangle.x < 0 || rectangle.x > (screen_width_ - rectangle.w) || checkRectangleCollisions(rectangle, walls_))
  {
    return false;
  }
  if (rectangle.y < 0 || rectangle.y > (screen_height_ - rectangle.h) || checkRectangleCollisions(rectangle, walls_))
  {
    return false;
  }

  return true;
}

bool Game::update() {
  if (!pacman_.alive())
  {
    std::cout << "pacman is dead" << std::endl;
    return false;
  }


  moveCharacter<Pacman>(pacman_);

  for (auto &ghost : ghosts_)
  {
    ghost->moveMethod();
    moveCharacter<Ghosts::Ghost>(*ghost);
  }

  handlePacmanDotCollisions(pacman_, dots_);
  if (handlePacmanDotCollisions(pacman_, pellets_))
  {
    // TODO: ghosts get scared and edible
  }

  for (auto &ghost : ghosts_)
  {
    // TODO: to be representative of pacman die once the ghost completely or almost completely overlaps pacman
    //       not when they start to touch
    if (checkRectangleCollision<SDL_FRect, SDL_FRect>(pacman_, *ghost))
    {
      pacman_.alive(false);
    }
  }

  return true;
}

int Game::score() const
{
  return score_;
}
