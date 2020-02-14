cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
add_executable(PacmanGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/pacman.cpp)

add_subdirectory(thirdparty/SDL2-2.0.10)
target_link_libraries(PacmanGame SDL2)


