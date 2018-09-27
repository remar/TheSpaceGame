// -*- mode: c++ -*-

#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "GameState.h"
#include "Asteroid.h"
#include "Spaceship.h"
#include "ObjectSpec.h"
#include <list>

class LevelState : public GameState {
public:
  void EnterState();
  void ExitState();
  void Update(GameLogic *gameLogic, float delta);

  static LevelState* Instance() { return &instance; }

private:
  static LevelState instance;

  Spaceship *spaceship;
  float backgroundScroll;
  float levelScroll;
  const float leftOfScreenOffset = -300;
  const float rightOfScreenOffset = 500;
  std::list<Asteroid *> asteroids;
  std::list<ObjectSpec> objectQueue;
};

#endif
