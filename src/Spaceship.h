// -*- mode: c++ -*-

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "GameObject.h"

class Spaceship : public GameObject {
public:
  Spaceship();
  virtual void update(float delta);
  void moveToward(float x, float y);

private:
  int fire;
};

#endif
