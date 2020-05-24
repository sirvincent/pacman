#pragma once

#include "image_loader.h"
#include "memory.h"

#include <SDL2/SDL_rect.h>



// TODO: is it an idea to move ImageLoader code into SpriteSheet? If ImageLoader unused, that might be better
class SpriteSheet : public ImageLoader
{
public:
  SpriteSheet(std::filesystem::path const &executable_path, std::string const &relative_to_assets_path_name);

  SDL_Surface load_rectangle_of_sprite_sheet(int const y_offset, int const x_offset, int const width, int const height);

private:
  memory::unique_surface_ptr sprite_sheet_;
};
