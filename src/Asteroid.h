// -*- mode: c++ -*-

#ifndef ASTEROID_H
#define ASTEROID_H

#include "GameObject.h"

class Asteroid : public GameObject {
public:
  Asteroid();
  virtual void update(float delta);
};

#endif
