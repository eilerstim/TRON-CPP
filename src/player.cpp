#include "player.h"
#include <cmath>
#include <iostream>
#include "game.h"

Player::Player(int grid_width, int grid_height, Player const &opponent, int type, Portal &portal) : 
        grid_width(grid_width),
        grid_height(grid_height),
        enemy(opponent),
        portal(portal) {
          if (type == Game::kBlue) {
            // If it is a user, set coordinates to the left edge of the screen.
            head_x = static_cast<float>(0);
            head_y = static_cast<float>(grid_height / 2);
            direction = Direction::kRight;
          }
          else if (type == Game::kOrange) {
            // If it is a program, set coordinates to the right edge of the screen.
            head_x = static_cast<float>(grid_width);
            head_y = static_cast<float>(grid_height / 2);
            direction = Direction::kLeft;
          }
        }

void Player::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // We first capture the head's cell before updating.
  
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the player head has moved to a new cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Player::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Check if the player is entering the portal.
  // This further prevents the player from having the portal point as part
  // of his trail because the head is directly set to a new random location.
  if (static_cast<int>(head_x) == static_cast<int>(portal.pos_x) && static_cast<int>(head_y) == static_cast<int>(portal.pos_y)) {
    // Set head coordinates to a random position on the grid
    head_x = portal.random_w(portal.engine);
    head_y = portal.random_h(portal.engine);
  }

  // Wrap the Player around to the beginning if going off of the screen
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);

}

void Player::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {

  if(trail == true)
    // Add length to trail by adding previous head location to vector.
    body.push_back(prev_head_cell);
  else {
    // When the trail is switched off, let it fade slowly.
    if (!body.empty())
      body.erase(body.begin());
  }
  // Let the trail fade if it becomes too long.
  if(body.size()>kMaxSize)
    body.erase(body.begin());

  //Check for collision with opponent's trail
  for (auto const &item : enemy.body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }

  // Check for collision with own trail
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}