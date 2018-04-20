#include "GameObject.h"
#include "Cats.h"
#include <cmath>

GameObject::GameObject(std::string sprite) {
  spriteId = Cats::CreateSpriteInstance(sprite);
}

void GameObject::setBoundingRadius(float radius) {
  boundingRadius = radius;
}

void GameObject::setPosition(float x, float y) {
  this->x = x;
  this->y = y;
  Cats::SetSpritePosition(spriteId, x, y);
}

inline float square(float x) {return x*x;}

bool GameObject::collides(const GameObject &other) {
  // Collision if distance is less than the sum of the radii.
  // Both sides can be squared to speed up calculation:
  // x^2+y^2 < (radius1 + radius2)^2
  return (square(abs(x - other.x)) + square(abs(y - other.y)))
    < square(other.boundingRadius + boundingRadius);
}
