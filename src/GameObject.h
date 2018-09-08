// -*- mode: c++ -*-

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include "Vector.h"

class GameObject {
public:
  GameObject(std::string sprite);
  virtual void update(float delta) = 0;
  void setBoundingRadius(float radius);
  void setPosition(float x, float y);
  bool collides(const GameObject *other);
  void setDirection(float dx, float dy);
  void setDirection(Vector v);
  void moveInDirection(float delta, float speed);

protected:
  float x;
  float y;
  int spriteId;
  float boundingRadius;
  Vector direction;
};

#endif
