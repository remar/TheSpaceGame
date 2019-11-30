#include "Asteroid.h"
#include "Button.h"
#include "Cats.h"
#include "Command.h"
#include "Constants.h"
#include "EditorObject.h"
#include "EditorState.h"
#include "FileDialog.h"
#include "Input.h"
#include "PlaceCommand.h"
#include <iostream>
#include <list>
#include <vector>

EditorState EditorState::instance;

struct ButtonSpec {
  std::string type;
  std::function<void()> callback;
};

int asteroid;

EditorObjectStore objects;

std::list<Command *> commands;

void EditorState::EnterState() {
  buttonBeingPressed = nullptr;
  editorMode = EditorMode::SELECTION_MODE;
  spriteFollowingMouse = -1;

  Cats::ShowPointer(true);

  std::vector<ButtonSpec> buttonSpecs {
    {"new", [](){instance.NewLevel();}},
    {"open", [](){instance.OpenLevel();}},
    {"selection", [](){instance.SelectionMode();}},
    {"large_asteroid", [](){instance.SelectObject(ObjectType::LARGE_ASTEROID);}},
  };

  int i = 0;
  for(auto b : buttonSpecs) {
    buttons.push_back(new Button(b.type, screenWidth - buttonWidth, i * buttonHeight, b.callback));
    i += 1;
  }
}

void EditorState::ExitState() {
  if(spriteFollowingMouse != -1) {
    Cats::RemoveSpriteInstance(spriteFollowingMouse);
  }

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
    if(x > screenWidth - buttonWidth) {
      buttonBeingPressed = ButtonAt(x, y);
      if(buttonBeingPressed != nullptr) {
	buttonBeingPressed->SetPressedState(true);
      }
    } else {
      // Not in toolbar: interact with actual game field
      if(editorMode == EditorMode::PLACEMENT_MODE) {
	commands.push_back(new PlaceCommand(objects, selectedObjectType, x, y));
	commands.back()->Execute();
	std::cout << "commands: " << commands.size() << std::endl;
      } else if(editorMode == EditorMode::SELECTION_MODE) {
	auto object = objects.GetObjectAt(x, y);
	if(object != nullptr) {
	  std::cout << "found object: " << object->objectId << std::endl;
	  objects.Remove(object->objectId);
	}
      }
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
  if(Input::instance.mouseMovement(x, y) && spriteFollowingMouse != -1) {
    Cats::ShowSprite(spriteFollowingMouse, x < screenWidth - buttonWidth);
    Cats::SetSpritePosition(spriteFollowingMouse, x, y);
  }
}

void EditorState::NewLevel() {
  std::cout << "Create a new level!" << std::endl;
}

void EditorState::OpenLevel() {
  std::cout << "File: " << ChooseFile() << std::endl;
}

void EditorState::SelectionMode() {
  std::cout << "Selection mode" << std::endl;
  editorMode = EditorMode::SELECTION_MODE;

  if(spriteFollowingMouse != -1) {
    Cats::RemoveSpriteInstance(spriteFollowingMouse);
    spriteFollowingMouse = -1;
  }
}

void EditorState::SelectObject(ObjectType type) {
  std::cout << "Select object: " << type << std::endl;
  editorMode = EditorMode::PLACEMENT_MODE;
  selectedObjectType = type;

  // TODO: Set sprite according to the object type selected
  spriteFollowingMouse = Cats::CreateSpriteInstance("asteroid1");

  // Hide sprite until mouse is moved out from toolbar
  Cats::ShowSprite(spriteFollowingMouse, false);
}

Button *EditorState::ButtonAt(int x, int y) {
  if(x >= screenWidth - buttonWidth && y/buttonHeight < buttons.size()) {
    return buttons[y / buttonHeight];
  }
  return nullptr;
}
