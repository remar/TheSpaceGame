// -*- mode: c++ -*-

#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "GameState.h"
#include "Button.h"
#include <vector>
#include "ObjectSpec.h"

class EditorState : public GameState {
public:
  void EnterState();
  void ExitState();
  void Update(GameLogic *gameLogic, float delta);

  static EditorState* Instance() { return &instance; }
  static EditorState instance;

private:

  enum EditorMode {
    SELECTION_MODE,
    PLACEMENT_MODE
  };

  void NewLevel();
  void OpenLevel();
  void SelectionMode();
  void SelectObject(ObjectType type);
  Button *ButtonAt(int x, int y);
  std::vector<Button *> buttons;
  Button *buttonBeingPressed;
  EditorMode editorMode;
  int spriteFollowingMouse;
  ObjectType selectedObjectType;
};

#endif
