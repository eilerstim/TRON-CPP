#include "snake.h"
#include <cmath>
#include <iostream>
#include "game.h"

Snake::Snake(int grid_width, int grid_height, Snake const &opponent, int random_w, int random_h) : 
        grid_width(grid_width),
        grid_height(grid_height),
        head_x(random_w),
        head_y(random_h),
        enemy(opponent) {}

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
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

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  if(trail == true)
    // Add length to trail by adding previous head location to vector
    body.push_back(prev_head_cell);
  else {
    // When the trail is switched off, let it fade slowly
    if (!body.empty())
      body.erase(body.begin());
  }
  // Let the trail fade if it becomes too long
  if(body.size()>kMaxSize)
    body.erase(body.begin());

  // How to remove non-connected trails?? Tried with loop that checks distance between the next node and if bigger than 2 will erase the last element

  //Check for collision with opponent's trail
  for (auto const &item : enemy.body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}
