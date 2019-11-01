#include "EditorState.h"
#include <iostream>
#include "FileDialog.h"
#include "Input.h"
#include "Cats.h"
#include "Button.h"
#include "Constants.h"
#include <vector>

EditorState EditorState::instance;

struct ButtonSpec {
  std::string type;
  std::function<void()> callback;
};

int asteroid;

void EditorState::EnterState() {
  buttonBeingPressed = nullptr;

  asteroid = Cats::CreateSpriteInstance("asteroid1");
  Cats::ShowPointer(true);

  std::vector<ButtonSpec> buttonSpecs {
    {"new", [](){instance.NewLevel();}},
    {"open", [](){instance.OpenLevel();}},
  };

  int i = 0;
  for(auto b : buttonSpecs) {
    buttons.push_back(new Button(b.type, screenWidth - buttonWidth, i * buttonHeight, b.callback));
    i += 1;
  }
}

void EditorState::ExitState() {
  for(auto button : buttons) {
    delete button;
  }
}

void EditorState::Update(GameLogic *gameLogic, float delta) {
  if(Input::instance.pressed(SDLK_o)) {
    OpenLevel();
  }
  int x, y;
  if(Input::instance.mouseButtonDown(x, y)) {
    buttonBeingPressed = ButtonAt(x, y);
    if(buttonBeingPressed != nullptr) {
      buttonBeingPressed->SetPressedState(true);
    }
  }
  if(Input::instance.mouseButtonUp(x, y)) {
    for(auto b : buttons) {
      b->SetPressedState(false);
    }
    Button *buttonBeingReleased = ButtonAt(x, y);
    if(buttonBeingReleased != nullptr && buttonBeingPressed == buttonBeingReleased) {
      buttonBeingReleased->Press();
    }
  }
  if(Input::instance.mouseMovement(x, y)) {
    // Just an example of following the mouse pointer
    Cats::SetSpritePosition(asteroid, x, y);
  }
}

void EditorState::NewLevel() {
  std::cout << "Create a new level!" << std::endl;
}

void EditorState::OpenLevel() {
  std::cout << "File: " << ChooseFile() << std::endl;
}

Button *EditorState::ButtonAt(int x, int y) {
  if(x >= screenWidth - buttonWidth && y/buttonHeight < buttons.size()) {
    return buttons[y / buttonHeight];
  }
  return nullptr;
}
