#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"

// Controller class that handles all keyboard presses
class Controller {
 public:
  void HandleInput(bool &running, Player &user,Player &program) const;
  void ManageStart(bool &start, bool &running) const;

 private:
  void ChangeDirection(Player &player, Player::Direction input,
                       Player::Direction opposite) const;
  void Reset(Player &user,Player &program) const;
};

#endif