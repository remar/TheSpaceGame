// -*- mode: c++ -*-

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include "Vector.h"

class GameObject {
public:
  GameObject(std::string sprite);
  ~GameObject() { destroy(); }
  virtual void update(float delta) = 0;
  void setBoundingRadius(float radius);
  void setWorldPosition(float worldX, float worldY);
  void setCameraPosition(float cameraX, float cameraY);
  float getWorldXPosition() { return worldX; }
  float getWorldYPosition() { return worldY; }
  float getScreenXPosition() { return worldX - cameraX; }
  float getScreenYPosition() { return worldY - cameraY; }
  bool collides(const GameObject *other);
  void setDirection(float dx, float dy);
  void setDirection(Vector v);
  void moveInDirection(float delta, float speed);
  virtual void destroy();
  bool isBeingDestroyed() { return toBeDestroyed; }

protected:
  void updateGraphicsPosition();
  float worldX;
  float worldY;
  float cameraX;
  float cameraY;
  int spriteId;
  float boundingRadius;
  Vector direction;
  bool toBeDestroyed;
};

#endif
