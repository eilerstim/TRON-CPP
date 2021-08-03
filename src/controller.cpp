#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake1, Snake &snake2) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_w:
          ChangeDirection(snake1, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_s:
          ChangeDirection(snake1, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_a:
          ChangeDirection(snake1, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_d:
          ChangeDirection(snake1, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
        case SDLK_q:
          snake1.speed == 0.1f ? snake1.speed = 0.2f : snake1.speed = 0.1f;
          break;
        case SDLK_e:
          snake1.trail == false ? snake1.trail = true : snake1.trail = false;
          break;
        case SDLK_i:
          ChangeDirection(snake2, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_k:
          ChangeDirection(snake2, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_j:
          ChangeDirection(snake2, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_l:
          ChangeDirection(snake2, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
        case SDLK_u:
          snake2.speed == 0.1f ? snake2.speed = 0.2f : snake2.speed = 0.1f;
          break;
        case SDLK_o:
          snake2.trail == false ? snake2.trail = true : snake2.trail = false;
          break;
      }
    }
  }
}