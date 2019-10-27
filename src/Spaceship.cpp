#include "Spaceship.h"
#include "Cats.h"

Spaceship::Spaceship() : GameObject("rymdskepp") {
  fire = Cats::CreateSpriteInstance("stor_eld");
  setBoundingRadius(40);
  direction.set(0, 0);
}

Spaceship::~Spaceship() {
  Cats::RemoveSpriteInstance(fire);
}

void Spaceship::update(float delta) {
  moveInDirection(delta, 300);

  // Follow camera (camera moves 200 pixels to the right each second)
  direction.set(1, 0);
  moveInDirection(delta, 200);

  Cats::SetSpritePosition(fire, getScreenXPosition() - 60, getScreenYPosition());
}

void Spaceship::show(bool show) {
  GameObject::show(show);
  Cats::ShowSprite(fire, show);
}
