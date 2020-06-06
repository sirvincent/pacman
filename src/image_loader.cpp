#include "image_loader.h"
#include "memory.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>


ImageLoader::ImageLoader(std::filesystem::path const &executable_path)
{
    std::filesystem::path absolute_path = std::filesystem::absolute(executable_path);
    assets_path_ = std::filesystem::canonical(absolute_path.parent_path() / ".." / "assets");

    assert(std::filesystem::exists(assets_path_));

    IMG_Init(IMG_INIT_PNG);
}


ImageLoader::~ImageLoader()
{
  // does not free, only unloads
  IMG_Quit();
}


memory::unique_surface_ptr ImageLoader::load_asset(std::string const &relative_to_assets_path_name)
{
  // TODO: handle if extension is given in relative_to_assets_path_name
  std::filesystem::path asset_path = assets_path_ / relative_to_assets_path_name;

  memory::unique_surface_ptr surface(IMG_Load(asset_path.c_str()));

  return surface;
}

