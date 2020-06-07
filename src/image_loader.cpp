#include "image_loader.h"
#include "memory.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>


ImageLoader::ImageLoader(std::filesystem::path const &executablePath)
{
  std::filesystem::path absolutePath = std::filesystem::absolute(executablePath);
  assetsPath_                        = std::filesystem::canonical(absolutePath.parent_path() / ".." / "assets");

  assert(std::filesystem::exists(assetsPath_));

  IMG_Init(IMG_INIT_PNG);
}


ImageLoader::~ImageLoader()
{
  // does not free, only unloads
  IMG_Quit();
}


memory::unique_surface_ptr ImageLoader::loadAsset(std::string const &relativeToAssetsPathName)
{
  // TODO: handle if extension is given in relativeToAssetsPathName
  std::filesystem::path assetPath = assetsPath_ / relativeToAssetsPathName;

  memory::unique_surface_ptr surface(IMG_Load(assetPath.c_str()));

  return surface;
}
