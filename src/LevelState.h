#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "GameState.h"
#include "Asteroid.h"
#include "Spaceship.h"

class LevelState : public GameState {
public:
  void EnterState();
  void ExitState();
  void Update(GameLogic *gameLogic, float delta);

  static LevelState* Instance() { return &instance; }

private:
  static LevelState instance;
  Asteroid *asteroid;
  Spaceship *spaceship;
  float scroll;
};

#endif
