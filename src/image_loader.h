#pragma once

#include "memory.h"

#include <filesystem>
#include <string>
#include <cassert>
#include <iostream>


class ImageLoader
{
public:
  ImageLoader(std::filesystem::path const &executablePath);
  ~ImageLoader();

  memory::unique_surface_ptr loadAsset(std::string const &relativeToAssetsPathName);

private:
  std::filesystem::path assetsPath_;
};
