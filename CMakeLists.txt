cmake_minimum_required(VERSION 3.15)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.256.tar.gz"
    SHA1 "e9b8328133fc0643d5f921fec81f2c0808c98419"
)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

hunter_add_package(SDL2)
find_package(SDL2 CONFIG REQUIRED)

hunter_add_package(SDL_image)
find_package(DL_image CONFIG REQUIRED)

file(GLOB sources "src/*.cpp")
add_executable(PacmanGame ${sources})

target_link_libraries(PacmanGame PUBLIC SDL2::SDL2 SDL_image::SDL_image)
