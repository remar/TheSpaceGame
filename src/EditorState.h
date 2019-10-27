// -*- mode: c++ -*-

#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "GameState.h"

class EditorState : public GameState {
public:
  void EnterState();
  void ExitState();
  void Update(GameLogic *gameLogic, float delta);

  static EditorState* Instance() { return &instance; }
  static EditorState instance;
};

#endif
