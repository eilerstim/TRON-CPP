#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : user(grid_width, grid_height, program, Game::blue, portal), 
      program(grid_width, grid_height, user, Game::orange, portal),
      portal(grid_width, grid_height)
      {}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true; // Will be set to false if we close the window
  bool start = false;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    if (start) {
      controller.HandleInput(running, user, program);
      Update();
    }
    else {
      // Wait for a button press before starting the game
      controller.ManageStart(start, running);
    }
    // Fill screen with the winner's color or continue rendering the game
    if (!user.alive && !program.alive) 
      renderer.Fill(draw);
    else if (user.alive && !program.alive)
      renderer.Fill(blue);
    else if (!user.alive && program.alive)
      renderer.Fill(orange);
    else
      renderer.Render(user, program, portal);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  // Do not update position if someone is not alive
  if (!user.alive || !program.alive) 
    return;

  user.Update();
  program.Update();

}