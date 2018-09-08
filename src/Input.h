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

  static Input* Instance() { return &instance; }

private:
  float dx, dy;
  bool quitEvent;
  static Input instance;
};

#endif
