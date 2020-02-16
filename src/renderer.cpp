#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width_(screen_width),
      screen_height_(screen_height),
      grid_width_(grid_width),
      grid_height_(grid_height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_window_ = SDL_CreateWindow("pacman Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (sdl_window_ == nullptr) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
  if (sdl_renderer_ == nullptr) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window_);
  SDL_Quit();
}

void Renderer::render(Pacman const &pacman, std::vector<Dot> const &dots_, std::vector<Dot> const &pellets_, std::vector<SDL_Rect> const &walls_)
{
  SDL_SetRenderDrawColor(sdl_renderer_, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer_);

  // draw pacman
  SDL_SetRenderDrawColor(sdl_renderer_, 0xFF, 0xFF, 0x00, 0xFF);
  SDL_RenderFillRectF(sdl_renderer_, &pacman);


  // draw grid
  std::size_t ratio_width = screen_width_ / grid_width_;
  std::size_t ratio_height = screen_height_ / grid_height_;
  SDL_SetRenderDrawColor(sdl_renderer_, 0x7D, 0x3C, 0x98, 0xFF);
  for (std::size_t w = 0; w < ratio_width; ++w)
  {
    SDL_RenderDrawLine(sdl_renderer_, w * grid_width_, 0, w * grid_width_, screen_height_);
  }
  for (std::size_t h = 0; h < ratio_height; ++ h)
  {
    SDL_RenderDrawLine(sdl_renderer_, 0, h * grid_height_, screen_width_, h * grid_height_);
  }


  SDL_SetRenderDrawColor(sdl_renderer_, 0x00, 0x51, 0xFF, 0xFF);
  for (Dot dot : dots_)
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

  SDL_SetRenderDrawColor(sdl_renderer_, 0x00, 0xAF, 0xFF, 0xFF);
  for (Dot pellet : pellets_)
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

  SDL_SetRenderDrawColor(sdl_renderer_, 0xA4, 0x54, 0x00, 0xFF);
  for (SDL_Rect wall : walls_)
  {
    SDL_RenderFillRect(sdl_renderer_, &wall);
  }


  SDL_RenderPresent(sdl_renderer_);
}

void Renderer::updateWindowTitle(int score, int fps) {
  std::string title{"pacman Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window_, title.c_str());
}
