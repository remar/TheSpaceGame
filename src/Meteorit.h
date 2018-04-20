// -*- mode: c++ -*-

#ifndef METEORIT_H
#define METEORIT_H

#include "GameObject.h"

class Meteorit : public GameObject {
public:
  Meteorit();
  virtual void update(float delta);
};

#endif
