// -*- mode: c++ -*-

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

class GameState;

class GameLogic {
public:
  GameLogic();
  void ChangeState(GameState *gameState);
  void Update(float delta);

private:
  GameState *currentState;
};

#endif
