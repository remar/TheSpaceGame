#include "Button.h"
#include "Cats.h"

Button::Button(std::string type, int x, int y) : x(x), y(y) {
  buttonId = Cats::CreateSpriteInstance("buttons");
  Cats::SetAnimation(buttonId, "unpressed");
  buttonContentId = Cats::CreateSpriteInstance("buttons");
  Cats::SetAnimation(buttonContentId, type);
  Cats::SetSpritePosition(buttonId, x, y);
  Cats::SetSpritePosition(buttonContentId, x, y);
}

Button::~Button() {
  Cats::RemoveSpriteInstance(buttonId);
  Cats::RemoveSpriteInstance(buttonContentId);
}

void Button::SetPressedState(bool pressed) {
  Cats::SetAnimation(buttonId, pressed ? "pressed" : "unpressed");
  Cats::SetSpritePosition(buttonContentId,
			  x + (pressed ? 3 : 0),
			  y + (pressed ? 3 : 0));
}
