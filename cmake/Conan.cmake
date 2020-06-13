macro(run_conan)
# Download automatically, you can also just copy the conan.cmake file
# TODO: before usage test if works:
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(
    STATUS
      "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
       "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_add_remote(NAME bincrafters URL
  https://api.bintray.com/conan/bincrafters/public-conan)

# TODO: what is the conan command to obtain options!?
# OUTDATED: options of sdl2: https://github.com/bincrafters/conan-sdl2
# OUTDATED: options of sdl2_image: https://github.com/bincrafters/conan-sdl2_image
# options of spdlog: https://github.com/conan-io/conan-center-index/blob/master/recipes/spdlog/all/conanfile.py
# spdlog/1.6.1
set(CONAN_EXTRA_OPTIONS ${CONAN_EXTRA_OPTIONS} sdl2_image:bmp=False sdl2_image:gif=False sdl2_image:lbm=False
    sdl2_image:pcx=False sdl2_image:pnm=False sdl2_image:tga=False sdl2_image:xcf=False sdl2_image:xpm=False
    sdl2_image:xv=False sdl2_image:jpg=False sdl2_image:tif=False sdl2_image:webp=False)

conan_cmake_run(
  REQUIRES
  sdl2/2.0.12@bincrafters/stable
  sdl2_image/2.0.5@bincrafters/stable
  OPTIONS
  ${CONAN_EXTRA_OPTIONS}
  BASIC_SETUP
  CMAKE_TARGETS # individual targets to link to
  BUILD
  missing)
endmacro()
