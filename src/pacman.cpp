#include "pacman.h"
#include "image_loader.h"

#include <cmath>
#include <iostream>


Pacman::Pacman(float width, float height, float speed) : Movement(speed, speed, speed, speed), sprite_sheet_(nullptr)
{
  // x,y are initialized to 0.0f to circumvent uninitialized members
  x = 0.0f;
  y = 0.0f;
  w = width;
  h = height;
}

void Pacman::initialize_texture(SDL_Renderer *sdl_renderer_, std::filesystem::path const &executable_path)
{
  ImageLoader image_loader = ImageLoader(executable_path);
  // TODO: magic string replace with variable name
  memory::unique_surface_ptr surface = image_loader.load_asset("pac-classic/pac-classic_c-toy.png");

  assert(surface);

  sprite_sheet_ = SDL_CreateTextureFromSurface(sdl_renderer_, surface.get());

  assert(sprite_sheet_ != nullptr);
}

void Pacman::move()
{
  // TODO: currently movement is frame based, I prefer time based for understandable physics}
  x += velocity_x_;
  y += velocity_y_;
}

bool Pacman::alive() const
{
  return alive_;
}

void Pacman::alive(bool alive)
{
  alive_ = alive;
}

std::pair<SDL_Texture *, SDL_Rect> Pacman::active_sprite()
{
  switch (direction)
  {
    case Movement::Direction::up:
      return std::make_pair(sprite_sheet_, SDL_Rect{556, 853, 138, 170});
      break;
    case Movement::Direction::down:
      return std::make_pair(sprite_sheet_, SDL_Rect{556, 5, 138, 170});
      break;
    case Movement::Direction::left:
      return std::make_pair(sprite_sheet_, SDL_Rect{556, 342, 138, 170});
      break;
    case Movement::Direction::right:
      return std::make_pair(sprite_sheet_, SDL_Rect{556, 172, 138, 170});
      break;
  }
}
