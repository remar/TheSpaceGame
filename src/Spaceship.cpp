#include "Spaceship.h"
#include "Cats.h"
#include <cmath>

Spaceship::Spaceship() : GameObject("rymdskepp") {
  fire = Cats::CreateSpriteInstance("stor_eld");
  setBoundingRadius(40);
  direction.set(0, 0);
}

void Spaceship::update(float delta) {
  setPosition(x + direction.x * delta * 300, y + direction.y * delta * 300);
  Cats::SetSpritePosition(fire, x - 60, y);
}

void Spaceship::moveToward(float x, float y) {
  float epsilon = 1.0f;
  if(std::abs(x - this->x) < epsilon && std::abs(y - this->y) < epsilon) {
    direction.set(0, 0);
  } else {
    direction.set(x - this->x, y - this->y);
  }
  direction.normalize();
}
