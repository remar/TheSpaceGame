// -*- mode: c++ -*-

#ifndef RYMDSKEPP_H
#define RYMDSKEPP_H

#include "GameObject.h"

class Rymdskepp : public GameObject {
public:
  Rymdskepp();
  virtual void update(float delta);

private:
  int eld;
};

#endif
