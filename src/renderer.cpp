#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_window = SDL_CreateWindow("pacman Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (sdl_window == nullptr) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (sdl_renderer == nullptr) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::render(Pacman const &pacman, SDL_Point const &dot) {
  SDL_Rect block;
  block.w = grid_width;
  block.h = grid_height;

  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  /* TODO: implement me:
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = dot.x * block.w;
  block.y = dot.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
  */

  // draw pacman
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0x00, 0xFF);
  block.x = pacman.x * block.w;
  block.y = pacman.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);


  // draw grid
  std::size_t ratio_width = screen_width / grid_width;
  std::size_t ratio_height = screen_height / grid_height;
  SDL_SetRenderDrawColor(sdl_renderer, 0x7D, 0x3C, 0x98, 0xFF);
  for (std::size_t w = 0; w < ratio_width; ++w)
  {
    SDL_RenderDrawLine(sdl_renderer, w * grid_width, 0, w * grid_width, screen_height);
  }
  for (std::size_t h = 0; h < ratio_height; ++ h)
  {
    SDL_RenderDrawLine(sdl_renderer, 0, h * grid_height, screen_width, h * grid_height);
  }
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::updateWindowTitle(int score, int fps) {
  std::string title{"pacman Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
