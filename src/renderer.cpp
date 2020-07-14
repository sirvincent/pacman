#include "renderer.h"

#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screenWidth,
  const std::size_t screenHeight,
  const std::size_t gridWidth,
  const std::size_t gridHeight)
  : screenWidth_(screenWidth)
  , screenHeight_(screenHeight)
  , gridWidth_(gridWidth)
  , gridHeight_(gridHeight)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  sdlWindow_ = SDL_CreateWindow("pacman Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

  if (sdlWindow_ == nullptr)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  sdlRenderer_ = SDL_CreateRenderer(sdlWindow_, -1, SDL_RENDERER_ACCELERATED);
  if (sdlRenderer_ == nullptr)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(sdlWindow_);
  SDL_Quit();
}

void Renderer::initialize(Pacman &pacman, std::vector<std::unique_ptr<Ghosts::Ghost>> const &ghosts, std::filesystem::path const &executablePath)
{
  pacman.initializeTexture(sdlRenderer_, executablePath);
  for (std::unique_ptr<Ghosts::Ghost> const &ghost : ghosts)
  {
    ghost->initializeTexture(sdlRenderer_, executablePath);
  }
}

void Renderer::render(Pacman &pacman, std::vector<Dot> const &dots, std::vector<Dot> const &pellets, std::vector<SDL_Rect> const &walls, std::vector<std::unique_ptr<Ghosts::Ghost>> const &ghosts)
{
  SDL_SetRenderDrawColor(sdlRenderer_, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdlRenderer_);

  // draw pacman
  auto [pacman_texture, pacman_texture_rectangle] = pacman.activeSprite();
  SDL_RenderCopyF(sdlRenderer_, pacman_texture, &pacman_texture_rectangle, &pacman);


  SDL_SetRenderDrawColor(sdlRenderer_, 0xF9, 0xE7, 0x9F, 0xFF);
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
    SDL_RenderFillRect(sdlRenderer_, &rectangle);
  }

  SDL_SetRenderDrawColor(sdlRenderer_, 0xF9, 0xE7, 0x9F, 0xFF);
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
    SDL_RenderFillRect(sdlRenderer_, &rectangle);
  }

  SDL_SetRenderDrawColor(sdlRenderer_, 0x0D, 0x44, 0xAF, 0xFF);
  for (SDL_Rect wall : walls)
  {
    SDL_RenderFillRect(sdlRenderer_, &wall);
  }

  for (std::unique_ptr<Ghosts::Ghost> const &ghost : ghosts)
  {
    auto [ghost_texture, ghost_texture_rectangle] = ghost->activeSprite();
    SDL_RenderCopyF(sdlRenderer_, ghost_texture, &ghost_texture_rectangle, ghost.get());
  }


  SDL_RenderPresent(sdlRenderer_);
}

void Renderer::updateWindowTitle(int score, int fps)
{
  std::string title{"pacman Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdlWindow_, title.c_str());
}
