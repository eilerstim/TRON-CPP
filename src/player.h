#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "portal.h"
#include "SDL.h"

class Player {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Player(int grid_width, int grid_height, Player const &opponent, int type, Portal &portal);
  static constexpr std::size_t kMaxSize{20};
  void Update();

  Direction direction;
  float speed{0.1f};
  const int size{7};
  bool trail{false};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  Player const &enemy;
  Portal &portal;
  int getGridWidth() {return grid_width;};
  int getGridHeight() {return grid_height;};

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  int grid_width;
  int grid_height;
};

#endif