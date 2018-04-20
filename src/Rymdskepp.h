// -*- mode: c++ -*-

#ifndef RYMDSKEPP_H
#define RYMDSKEPP_H

#include "GameObject.h"

class Rymdskepp : public GameObject {
public:
  Rymdskepp();
  virtual void update();

private:
  int eld;
};

#endif
