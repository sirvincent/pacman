#pragma once

#include "SDL.h"

#include <utility>
#include <filesystem>


// a pure virtual interface class, following Core Guidelines C.129 design class hierarchy
class SpriteGraphics
{
public:
  virtual std::pair<SDL_Texture *, SDL_Rect> activeSprite()                                                 = 0;
  virtual void initializeTexture(SDL_Renderer *sdlRenderer_, std::filesystem::path const &executablePath) = 0;

private:
};


// dual hierarchy example of C.129, the corresponding implementation class
// TODO: better to move to separate file?
namespace Implementation {
class SpriteGraphics : public virtual ::SpriteGraphics
{
public:
  explicit SpriteGraphics(std::string const &relative_path_sprite_sheet_to_assets_directory);
  void initializeTexture(SDL_Renderer *sdlRenderer_, std::filesystem::path const &executablePath) override;


protected:
  // sprite_sheet is owned by renderer, not by this class, this is not insightfull but is required
  // since it is rendered in a hardware optimized way, so the hardware owns it (renderer)
  SDL_Texture *spriteSheet_;

private:
  std::string const relativePathSpriteSheetToAssetsDirectory_;
};
}  // namespace Implementation
