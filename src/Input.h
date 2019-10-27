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

  /* Checks if key has been pressed since last update (only returns
     'true' once for each keypress) */
  bool pressed(int key);

  static Input instance;

private:
  float dx, dy;
  bool quitEvent;
};

#endif
