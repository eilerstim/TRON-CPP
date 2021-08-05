#include "renderer.h"
#include "game.h"
#include "portal.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Player Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);
  // Check if it was able to open up
  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Player const user, Player const program, Portal const &portal) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render user's body (blue)
  SDL_SetRenderDrawColor(sdl_renderer, 0x26, 0xB4, 0xCA, 0xFF);
  for (SDL_Point const &point : user.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render user's head
  block.x = static_cast<int>(user.head_x) * block.w;
  block.y = static_cast<int>(user.head_y) * block.h;
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xEA, 0xFF, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &block);

    // Render program's body (orange)
  SDL_SetRenderDrawColor(sdl_renderer, 0xDF, 0x74, 0x0C, 0xFF);
  for (SDL_Point const &point : program.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render program's head (orange)
  block.x = static_cast<int>(program.head_x) * block.w;
  block.y = static_cast<int>(program.head_y) * block.h;
  SDL_SetRenderDrawColor(sdl_renderer, 0xF7, 0x9D, 0x1E, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &block);

  // Color every block around the portal white
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : portal.border) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

// Print name and FPS Counter to window title
void Renderer::UpdateWindowTitle(int fps) {
  std::string title{"TRON: " + std::to_string(fps) + " FPS"};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::Fill(int winner) {
  // fill screen with the winner's color (white in case of a draw)
  if (winner == Game::draw) {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(sdl_renderer);
  }
  else if (winner == Game::blue) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xEA, 0xFF, 0xFF);
    SDL_RenderClear(sdl_renderer);
  }
  else if (winner == Game::orange) {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x67, 0x00, 0xFF);
    SDL_RenderClear(sdl_renderer);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}