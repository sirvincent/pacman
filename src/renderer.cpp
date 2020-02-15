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

void Renderer::render(Pacman const &pacman, SDL_Point const &dot) {
  SDL_Rect block;
  block.w = grid_width_;
  block.h = grid_height_;

  SDL_SetRenderDrawColor(sdl_renderer_, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer_);

  /* TODO: implement me:
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = dot.x * block.w;
  block.y = dot.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
  */

  // draw pacman
  SDL_SetRenderDrawColor(sdl_renderer_, 0xFF, 0xFF, 0x00, 0xFF);
  block.x = pacman.x * block.w;
  block.y = pacman.y * block.h;
  SDL_RenderFillRect(sdl_renderer_, &block);


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
  SDL_RenderPresent(sdl_renderer_);

}

void Renderer::updateWindowTitle(int score, int fps) {
  std::string title{"pacman Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window_, title.c_str());
}
