#include "sprite_graphics.h"
#include "image_loader.h"


namespace Implementation {

SpriteGraphics::SpriteGraphics(std::string const &relative_path_sprite_sheet_to_assets_directory) : spriteSheet_(nullptr),
                                                                                                    relativePathSpriteSheetToAssetsDirectory_(relative_path_sprite_sheet_to_assets_directory) {}


void SpriteGraphics::initializeTexture(SDL_Renderer *sdlRenderer_, std::filesystem::path const &executablePath)
{
  ImageLoader image_loader           = ImageLoader(executablePath);
  memory::unique_surface_ptr surface = image_loader.loadAsset(relativePathSpriteSheetToAssetsDirectory_);

  assert(surface);

  spriteSheet_ = SDL_CreateTextureFromSurface(sdlRenderer_, surface.get());

  assert(spriteSheet_ != nullptr);
}


}  // namespace Implementation
