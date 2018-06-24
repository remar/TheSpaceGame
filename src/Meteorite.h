// -*- mode: c++ -*-

#ifndef METEORITE_H
#define METEORITE_H

#include "GameObject.h"

class Meteorite : public GameObject {
public:
  Meteorite();
  virtual void update(float delta);
};

#endif
