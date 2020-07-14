#include "controller.h"
#include "game.h"
#include "renderer.h"

#include <cassert>
#include <iostream>
#include <cstring>
#include <filesystem>

#define ASSERT_MESSAGE(exp, msg) assert(((void)msg, exp))


int main(int argc, char **argv)
{
  constexpr std::size_t framesPerSecond{60};
  constexpr std::size_t msPerFrame{1000 / framesPerSecond};
  constexpr std::size_t gridWidth{32};
  constexpr std::size_t gridHeight{32};
  constexpr std::size_t screenWidth{640 - gridWidth};
  constexpr std::size_t screenHeight{640 + gridHeight};

  // TODO: We should robustly obtain the executable path, argv[0] might fail.
  //       How do we do this? use Poco? Boost? whereami (https://github.com/gpakosz/whereami)?
  //       Preferably something OS independend
  // following the C++ ISO standard if argv[0]:
  // argv[0] shall be the pointer to the initial character of a null-terminated multibyte string
  // that represents the name used to invoke the program or ""
  // if argc is nonzero
  ASSERT_MESSAGE(argc != 0, "argc == 0 hence extracting the path name of executable will not work");
  ASSERT_MESSAGE(std::strcmp(argv[0], ""), "argv is empty hence executable path can not be found");

  std::filesystem::path const executablePath = std::filesystem::path(argv[0]);

  assert(screenWidth % gridWidth == 0);
  assert(screenHeight % gridHeight == 0);

  Renderer renderer(screenWidth, screenHeight, gridWidth, gridHeight);
  Controller controller;

  Game game(screenWidth, screenHeight, gridWidth, gridHeight, executablePath);
  game.run(controller, renderer, msPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.score() << "\n";
  return 0;
}
