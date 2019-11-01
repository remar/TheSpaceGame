// -*- mode: c++ -*-

#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "GameState.h"
#include "Button.h"
#include <vector>

class EditorState : public GameState {
public:
  void EnterState();
  void ExitState();
  void Update(GameLogic *gameLogic, float delta);

  static EditorState* Instance() { return &instance; }
  static EditorState instance;

private:
  void NewLevel();
  void OpenLevel();
  Button *ButtonAt(int x, int y);
  std::vector<Button *> buttons;
  Button *buttonBeingPressed;
};

#endif
