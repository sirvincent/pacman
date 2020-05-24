#include "spritesheet.h"

#include <SDL2/SDL_surface.h>


SpriteSheet::SpriteSheet(std::filesystem::path const &executable_path, std::string const &relative_to_assets_path_name)
  : ImageLoader(executable_path), sprite_sheet_(load_asset(relative_to_assets_path_name)) { }


SDL_Surface SpriteSheet::load_rectangle_of_sprite_sheet(int const y_offset, int const x_offset, int const width, int const height)
{
  SDL_Rect source_rectangle_to_copy = {x_offset, y_offset, width, height};

  // TODO: dynamically allocate in place of placing on Stack?
  SDL_Surface destination_surface;
  SDL_BlitSurface(sprite_sheet_.get(), &source_rectangle_to_copy, &destination_surface, NULL);

  // TODO: is it better to let the compiler use copy elison than explicitely moving? I think the former.
  return destination_surface;
}
