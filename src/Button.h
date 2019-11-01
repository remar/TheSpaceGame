// -*- mode: c++ -*-

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>

class Button {
public:
  Button(std::string type, int x, int y, std::function<void()> callback);
  ~Button();
  void SetPressedState(bool pressed);
  void Press() { callback(); }

private:
  int buttonId;
  int buttonContentId;
  int x, y;
  std::function<void()> callback;
};

#endif
