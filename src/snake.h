#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, Snake const &opponent, int random_w, int random_h);
  static constexpr std::size_t kMaxSize{20};
  void Update();

  Direction direction = Direction::kUp;

  float speed{0.1f};
  const int size{7};
  bool trail{false};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  Snake const &enemy;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  int grid_width;
  int grid_height;
};

#endif