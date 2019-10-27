// -*- mode: c++ -*-

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "GameObject.h"

class Spaceship : public GameObject {
public:
  Spaceship();
  virtual void update(float delta);
  virtual void show(bool show);

private:
  int fire;
};

#endif
