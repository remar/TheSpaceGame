// -*- mode: c++ -*-

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>

class GameObject {
public:
  GameObject(std::string sprite);
  virtual void update() = 0;
  void setBoundingRadius(float radius);
  void setPosition(float x, float y);
  bool collides(const GameObject &other);

protected:
  float x;
  float y;
  int spriteId;
  float boundingRadius;
};

#endif
