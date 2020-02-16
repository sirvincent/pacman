#include "controller.h"
#include "game.h"
#include "renderer.h"

#include <cassert>
#include <iostream>


int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  // The reason for - kGridWidth is since we want to have a middle in the level
  constexpr std::size_t kScreenWidth{640 - kGridWidth};
  constexpr std::size_t kScreenHeight{640 + kGridHeight};

  assert(kScreenWidth % kGridWidth == 0);
  assert(kScreenHeight % kGridHeight == 0);

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  game.run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.score() << "\n";
  return 0;
}
