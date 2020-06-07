#include "renderer.h"

#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
  const std::size_t screen_height,
  const std::size_t grid_width,
  const std::size_t grid_height)
  : screen_width_(screen_width),
    screen_height_(screen_height),
    grid_width_(grid_width),
    grid_height_(grid_height)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_window_ = SDL_CreateWindow("pacman Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);

  if (sdl_window_ == nullptr)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
  if (sdl_renderer_ == nullptr)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window_);
  SDL_Quit();
}

void Renderer::initialize(Pacman &pacman, std::vector<std::unique_ptr<Ghosts::Ghost>> const &ghosts, std::filesystem::path const &executable_path)
{
  pacman.initialize_texture(sdl_renderer_, executable_path);
  for (std::unique_ptr<Ghosts::Ghost> const &ghost : ghosts)
  {
    ghost->initialize_texture(sdl_renderer_, executable_path);
  }
}

void Renderer::render(Pacman &pacman, std::vector<Dot> const &dots, std::vector<Dot> const &pellets, std::vector<SDL_Rect> const &walls, std::vector<std::unique_ptr<Ghosts::Ghost>> const &ghosts)
{
  SDL_SetRenderDrawColor(sdl_renderer_, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer_);

  // draw pacman
  auto [pacman_texture, pacman_texture_rectangle] = pacman.active_sprite();
  SDL_RenderCopyF(sdl_renderer_, pacman_texture, &pacman_texture_rectangle, &pacman);


  SDL_SetRenderDrawColor(sdl_renderer_, 0xF9, 0xE7, 0x9F, 0xFF);
  for (Dot dot : dots)
  {
    SDL_Rect rectangle;
    rectangle.x = dot.x();
    rectangle.y = dot.y();
    rectangle.w = dot.radius();
    rectangle.h = dot.radius();
    // TODO: we start with rectangle dots, since there is no FillCircle. To make a circle we either:
    //       1) use a circle sprite with a circular bounding box for collisions
    //       2) draw multiple points to make a filled circle, using the midpoint circle algorithm
    SDL_RenderFillRect(sdl_renderer_, &rectangle);
  }

  SDL_SetRenderDrawColor(sdl_renderer_, 0xF9, 0xE7, 0x9F, 0xFF);
  for (Dot pellet : pellets)
  {
    SDL_Rect rectangle;
    rectangle.x = pellet.x();
    rectangle.y = pellet.y();
    rectangle.w = pellet.radius();
    rectangle.h = pellet.radius();
    // TODO: we start with rectangle dots, since there is no FillCircle. To make a circle we either:
    //       1) use a circle sprite with a circular bounding box for collisions
    //       2) draw multiple points to make a filled circle, using the midpoint circle algorithm
    SDL_RenderFillRect(sdl_renderer_, &rectangle);
  }

  SDL_SetRenderDrawColor(sdl_renderer_, 0x0D, 0x44, 0xAF, 0xFF);
  for (SDL_Rect wall : walls)
  {
    SDL_RenderFillRect(sdl_renderer_, &wall);
  }

  for (std::unique_ptr<Ghosts::Ghost> const &ghost : ghosts)
  {
    auto [ghost_texture, ghost_texture_rectangle] = ghost->active_sprite();
    SDL_RenderCopyF(sdl_renderer_, ghost_texture, &ghost_texture_rectangle, ghost.get());
  }


  SDL_RenderPresent(sdl_renderer_);
}

void Renderer::updateWindowTitle(int score, int fps)
{
  std::string title{"pacman Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window_, title.c_str());
}
