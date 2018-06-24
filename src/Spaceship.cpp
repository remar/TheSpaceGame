#include "Spaceship.h"
#include "Cats.h"

Spaceship::Spaceship() : GameObject("rymdskepp") {
  fire = Cats::CreateSpriteInstance("stor_eld");
  setBoundingRadius(40);
}

void Spaceship::update(float delta) {
  Cats::SetSpritePosition(fire, x - 60, y);
}
