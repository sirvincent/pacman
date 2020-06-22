cmake_minimum_required(VERSION 3.15)

project(Pacman CXX)

include(cmake/StandardProjectSettings.cmake)
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(cmake/StaticAnalyzers.cmake)


file(GLOB sources "src/*.cpp")
add_executable(PacmanGame ${sources})

# required by SDL2_image
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
if(!SDL2_FOUND)
  message(FATAL_ERROR "SDL was not found")
else()
  message("SDL2 was found ${SDL2_LIBRARIES}")
endif()

find_package(SDL2_image REQUIRED)
if(!SDL2_IMAGE_FOUND)
  message(FATAL_ERROR "SDL image was not found")
else()
  message("SDL2 image was found ${SDL2_IMAGE_LIBRARIES}")
endif()


target_link_libraries(PacmanGame PRIVATE project_options project_warnings ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})





