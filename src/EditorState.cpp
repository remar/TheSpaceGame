#include "EditorState.h"
#include <iostream>
#include "FileDialog.h"
#include "Input.h"

EditorState EditorState::instance;

void EditorState::EnterState() {
  
}

void EditorState::ExitState() {
  
}

void EditorState::Update(GameLogic *gameLogic, float delta) {
  if(Input::instance.pressed(SDLK_o)) {
    std::cout << "File: " << ChooseFile() << std::endl;
  }
}
