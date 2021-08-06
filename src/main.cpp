#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1280};
  constexpr std::size_t kScreenHeight{720};
  // Change grid size for a different "feel"
  constexpr std::size_t kGridWidth{96};
  constexpr std::size_t kGridHeight{54};

  // Initialize renderer object that creates a window
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  
  // The main game loop
  game.Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  
  return 0;
}