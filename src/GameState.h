// -*- mode: c++ -*-

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameLogic.h"

class GameState {
public:
  virtual void EnterState() = 0;
  virtual void ExitState() = 0;

  virtual void Update(GameLogic *gameLogic, float delta) = 0;
};

#endif
