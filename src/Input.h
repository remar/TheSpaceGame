// -*- mode: c++ -*-

#ifndef INPUT_H
#define INPUT_H

#include "Vector.h"

class Input {
public:
  Input();
  void update();
  Vector getDirection();
  bool gotQuitEvent();

private:
  float dx, dy;
  bool quitEvent;
};

#endif
