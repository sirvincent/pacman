cmake_minimum_required(VERSION 3.15)

# the cmake is inspired by: https://github.com/lefticus/cpp_starter_project/blob/master/CMakeLists.txt

project(pacman CXX)
# include(cmake/StandardProjectSettings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
# include(cmake/Sanitizers.cmake)
# enable_sanitizers(project_options)

# enable doxygen
# include(cmake/Doxygen.cmake)
# enable_doxygen()

# allow for static analysis options
# include(cmake/StaticAnalyzers.cmake)

# option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
# option(ENABLE_TESTING "Enable Test Builds" OFF)

# TODO: use PCH?

include(cmake/Conan.cmake)
run_conan()

# if(ENABLE_TESTING)
#   enable_testing()
#   message(
#     "Building Tests. Be sure to check out test/constexpr_tests for constexpr testing"
#   )
#   add_subdirectory(test)
# endif()

file(GLOB sources "src/*.cpp")
add_executable(PacmanGame ${sources})
target_link_libraries(PacmanGame PRIVATE project_options CONAN_PKG::sdl2 CONAN_PKG::sdl2_image)

