#include "GameLogic.h"
#include "GameState.h"

GameLogic::GameLogic() : currentState(nullptr) {}

void GameLogic::ChangeState(GameState *gameState) {
  if(currentState != nullptr) {
    currentState->ExitState();
  }
  currentState = gameState;
  currentState->EnterState();
}

void GameLogic::Update(float delta) {
  currentState->Update(this, delta);
}
