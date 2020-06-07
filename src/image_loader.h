#pragma once

#include "memory.h"

#include <filesystem>
#include <string>
#include <cassert>
#include <iostream>


class ImageLoader
{
public:
  ImageLoader(std::filesystem::path const &executable_path);
  ~ImageLoader();

  memory::unique_surface_ptr load_asset(std::string const &relative_to_assets_path_name);

private:
  std::filesystem::path assets_path_;
};
