#include "EditorState.h"
#include <iostream>
#include "FileDialog.h"
#include "Input.h"
#include "Cats.h"
#include "Button.h"
#include "Constants.h"

EditorState EditorState::instance;

Button *b;

void EditorState::EnterState() {
  Cats::ShowPointer(true);

  b = new Button("new", screenWidth - buttonWidth, 0);
}

void EditorState::ExitState() {
  delete b;
}

void EditorState::Update(GameLogic *gameLogic, float delta) {
  if(Input::instance.pressed(SDLK_o)) {
    std::cout << "File: " << ChooseFile() << std::endl;
  }
  if(Input::instance.pressed(SDLK_n)) {
    b->SetPressedState(true);
  }
  if(Input::instance.released(SDLK_n)) {
    b->SetPressedState(false);
  }
}
