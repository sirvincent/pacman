#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "spritesheet.h"

#include <cassert>
#include <iostream>
#include <cstring>
#include <filesystem>

#define ASSERT_MESSAGE(exp, msg) assert(((void)msg, exp))


int main(int argc, char **argv) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  // The reason for - kGridWidth is since we want to have a middle in the level
  constexpr std::size_t kScreenWidth{640 - kGridWidth};
  constexpr std::size_t kScreenHeight{640 + kGridHeight};

  // TODO: We should robustly obtain the executable path, argv[0] might fail.
  //       How do we do this? use Poco? Boost? whereami (https://github.com/gpakosz/whereami)?
  //       Preferably something OS independend
  // following the C++ ISO standard if argv[0]:
  // argv[0] shall be the pointer to the initial character of a null-terminated multibyte string
  // that represents the name used to invoke the program or ""
  // if argc is nonzero
  ASSERT_MESSAGE(argc != 0, "argc == 0 hence extracting the path name of executable will not work");
  ASSERT_MESSAGE(std::strcmp(argv[0], ""), "argv is empty hence executable path can not be found");

  std::filesystem::path executable_path = std::filesystem::path(argv[0]);

  assert(kScreenWidth % kGridWidth == 0);
  assert(kScreenHeight % kGridHeight == 0);

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

  SpriteSheet spritesheet(executable_path, "pac-classic_c-toy");

  Game game(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  game.run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.score() << "\n";
  return 0;
}
