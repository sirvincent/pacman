#include "sprite_graphics.h"
#include "image_loader.h"


namespace Implementation
{

SpriteGraphics::SpriteGraphics(std::string const &relative_path_sprite_sheet_to_assets_directory) :
  sprite_sheet_(nullptr),
  relative_path_sprite_sheet_to_assets_directory_(relative_path_sprite_sheet_to_assets_directory) { }


void SpriteGraphics::initialize_texture(SDL_Renderer *sdl_renderer_, std::filesystem::path const &executable_path)
{
  ImageLoader image_loader = ImageLoader(executable_path);
  memory::unique_surface_ptr surface = image_loader.load_asset(relative_path_sprite_sheet_to_assets_directory_);

  assert(surface);

  sprite_sheet_ = SDL_CreateTextureFromSurface(sdl_renderer_, surface.get());

  assert(sprite_sheet_ != nullptr);
}


}
