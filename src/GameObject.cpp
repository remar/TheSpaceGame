#include "GameObject.h"
#include "Cats.h"
#include <cmath>

GameObject::GameObject(std::string sprite) {
  spriteId = Cats::CreateSpriteInstance(sprite);
  worldX = 0;
  worldY = 0;
  cameraX = 0;
  cameraY = 0;
}

void GameObject::setBoundingRadius(float radius) {
  boundingRadius = radius;
}

void GameObject::setWorldPosition(float worldX, float worldY) {
  this->worldX = worldX;
  this->worldY = worldY;
  updateGraphicsPosition();
}

void GameObject::setCameraPosition(float cameraX, float cameraY) {
  this->cameraX = cameraX;
  this->cameraY = cameraY;
  updateGraphicsPosition();
}

inline float square(float x) {return x*x;}

bool GameObject::collides(const GameObject *other) {
  // Collision if distance is less than the sum of the radii.
  // Both sides can be squared to speed up calculation:
  // x^2+y^2 < (radius1 + radius2)^2
  return (square(abs(worldX - other->worldX)) + square(abs(worldY - other->worldY)))
    < square(other->boundingRadius + boundingRadius);
}

void GameObject::setDirection(float dx, float dy) {
  direction.set(dx, dy);
  direction.normalize();
}

void GameObject::setDirection(Vector v) {
  direction = v;
  direction.normalize();
}

void GameObject::moveInDirection(float delta, float speed) {
  this->worldX += direction.x * delta * speed;
  this->worldY += direction.y * delta * speed;
  updateGraphicsPosition();
}

void GameObject::updateGraphicsPosition() {
  Cats::SetSpritePosition(spriteId, worldX - cameraX, worldY - cameraY);
}
