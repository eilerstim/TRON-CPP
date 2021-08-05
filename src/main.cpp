#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1280};
  constexpr std::size_t kScreenHeight{720};
  constexpr std::size_t kGridWidth{96}; //was 32x32 at 640x640
  constexpr std::size_t kGridHeight{54};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  
  return 0;
}