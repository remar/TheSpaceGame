// -*- mode: c++ -*-

#ifndef EDITOR_OBJECT_H
#define EDITOR_OBJECT_H

#include "GameObject.h"

class EditorObject {
public:
  EditorObject() {}
  EditorObject(GameObject *gameObject, int objectId = 0);
  GameObject *heldObject;
  int objectId;
private:
  static int nextObjectId;
};

#endif
