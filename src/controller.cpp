#include "game.h"
#include <iostream>
#include "SDL.h"
#include "player.h"

void Controller::ManageStart(bool &start, bool &running) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      start = true;
    }
  }
}

void Controller::ChangeDirection(Player &player, Player::Direction input,
                                 Player::Direction opposite) const {
  if (player.direction != opposite || player.size == 1) 
    player.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Player &user, Player &program) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_w:
          ChangeDirection(user, Player::Direction::kUp,
                          Player::Direction::kDown);
          break;

        case SDLK_s:
          ChangeDirection(user, Player::Direction::kDown,
                          Player::Direction::kUp);
          break;

        case SDLK_a:
          ChangeDirection(user, Player::Direction::kLeft,
                          Player::Direction::kRight);
          break;

        case SDLK_d:
          ChangeDirection(user, Player::Direction::kRight,
                          Player::Direction::kLeft);
          break;
        case SDLK_q:
          // Toggle between high and low speed
          user.speed == 0.1f ? user.speed = 0.2f : user.speed = 0.1f;
          break;
        case SDLK_e:
          // Activate and deactivate trail
          user.trail == false ? user.trail = true : user.trail = false;
          break;
        case SDLK_i:
          ChangeDirection(program, Player::Direction::kUp,
                          Player::Direction::kDown);
          break;

        case SDLK_k:
          ChangeDirection(program, Player::Direction::kDown,
                          Player::Direction::kUp);
          break;

        case SDLK_j:
          ChangeDirection(program, Player::Direction::kLeft,
                          Player::Direction::kRight);
          break;

        case SDLK_l:
          ChangeDirection(program, Player::Direction::kRight,
                          Player::Direction::kLeft);
          break;
        case SDLK_u:
          program.speed == 0.1f ? program.speed = 0.2f : program.speed = 0.1f;
          break;
        case SDLK_o:
          program.trail == false ? program.trail = true : program.trail = false;
          break;
        case SDLK_RETURN:
          // Reset the game if it has finished by pressing enter
          if (!user.alive || !program.alive) {
            Reset(user,program);
          }
          break;
      }
    }
  }
}

void Controller::Reset(Player &user, Player &program) const{
  //reset all attributes of each player
  user.trail = false;
  user.alive = true;
  user.head_x = 0.0;
  user.head_y = static_cast<float>(user.getGridHeight() / 2);
  user.body.clear();
  user.direction = Player::Direction::kRight;
  user.speed = 0.1f;

  program.trail = false;
  program.alive = true;
  program.head_x = static_cast<float>(program.getGridWidth());
  program.head_y = static_cast<float>(program.getGridHeight() / 2);
  program.body.clear();
  program.direction = Player::Direction::kLeft;
  program.speed = 0.1f;
}