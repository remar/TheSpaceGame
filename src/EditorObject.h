// -*- mode: c++ -*-

#ifndef EDITOR_OBJECT_H
#define EDITOR_OBJECT_H

#include "GameObject.h"

class EditorObject {
public:
  EditorObject(GameObject *gameObject);
  GameObject *heldObject;
};

#endif
