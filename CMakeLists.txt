cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
file(GLOB sources "src/*.cpp")
add_executable(PacmanGame ${sources})

# TODO: first uncompress if compressed, use the FindZIP.cmake, circumvents attaching all the files loosely into git etc
add_subdirectory(thirdparty/SDL2-2.0.10)
target_link_libraries(PacmanGame SDL2)

# TODO: basicly I have no idea how to do this in cmake... the following works but it is not programmed deliberately...
#       expectation is that the program will fail on any computer than my own
# inspired by: https://stackoverflow.com/questions/5971921/building-a-library-using-autotools-from-cmake
include(ExternalProject)
ExternalProject_Add(libSDL2_image
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SDL2_image-2.0.5
  CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SDL2_image-2.0.5/configure --prefix=${CMAKE_CURRENT_SOURCE_DIR}/build/thirdparty/SDL2_image-2.0.5
  PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/build/thirdparty/SDL2_image-2.0.5
  BUILD_COMMAND ${MAKE}
  )
# inspired by: https://www.reddit.com/r/cmake/comments/b6vywy/externalproject_and_static_libraries/
add_library(SDL2_image STATIC IMPORTED)
file (MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/thirdparty/SDL2_image-2.0.5/include/)
set_target_properties (SDL2_image PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/build/thirdparty/SDL2_image-2.0.5/lib/libSDL2_image.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/build/thirdparty/SDL2_image-2.0.5/include/
)
target_link_libraries(PacmanGame SDL2_image)





