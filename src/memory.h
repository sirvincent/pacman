#pragma once

#include <SDL2/SDL_surface.h>

#include <memory>


namespace memory {

// taken from: https://stackoverflow.com/questions/28609454/confused-using-unique-ptr-and-a-custom-deleter
struct FreeSurface
{
  void operator()(SDL_Surface *surface) const
  {
    SDL_FreeSurface(surface);
  }
};

using unique_surface_ptr = std::unique_ptr<SDL_Surface, FreeSurface>;

}  // namespace memory
