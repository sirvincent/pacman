cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

file(GLOB sources "src/*.cpp")
add_executable(PacmanGame ${sources})

find_package(SDL2 REQUIRED)
if(!SDL2_FOUND)
  message(FATAL_ERROR "SDL was not found")
else()
  message("SDL2 was found ${SDL2_LIBRARY}")
endif()
target_link_libraries(PacmanGame PRIVATE ${SDL2_LIBRARY})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2_image REQUIRED)
if(!SDL2_IMAGE_FOUND)
  message(FATAL_ERROR "SDL image was not found")
else()
  message("SDL2 image was found ${SDL2_IMAGE_LIBRARIES}")
endif()
target_link_libraries(PacmanGame PRIVATE ${SDL2_IMAGE_LIBRARIES})





