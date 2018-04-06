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
  // Collision if distance^2 < (xdiff^2 + ydiff^2)
  return square(other.boundingRadius + boundingRadius)
    < (square(abs(x - other.x)) + square(abs(y - other.y)));
}
