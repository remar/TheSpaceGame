// -*- mode: c++ -*-

#ifndef BUTTON_H
#define BUTTON_H

#include <string>

class Button {
public:
  Button(std::string type, int x, int y);
  ~Button();
  void SetPressedState(bool pressed);

private:
  int buttonId;
  int buttonContentId;
  int x, y;
};

#endif
