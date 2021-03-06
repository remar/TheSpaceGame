// -*- mode: c++ -*-

#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "GameState.h"
#include "Asteroid.h"
#include "Spaceship.h"
#include "ObjectSpec.h"
#include "Constants.h"
#include <list>

class LevelState : public GameState {
public:
  void EnterState();
  void ExitState();
  void Update(GameLogic *gameLogic, float delta);
  void SetLevel(std::string level) { this->level = level; }

  static LevelState* Instance() { return &instance; }
  static LevelState instance;

private:
  void LoadLevel(std::string path);
  void StartLevel();
  void CreateAsteroidAt(float x, float y, ObjectType type);
  void SetCameraPosition(float x, float y);

  Spaceship *spaceship;
  float backgroundScroll;
  float levelScroll;
  const float leftOfScreenOffset = -300;
  const float rightOfScreenOffset = screenWidth + 500;
  std::list<Asteroid *> asteroids;
  std::list<ObjectSpec> objectQueue;
  std::list<ObjectSpec> originalObjectQueue;
  std::string level;
};

#endif
