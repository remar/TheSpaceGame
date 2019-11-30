#include "EditorObject.h"
#include <iostream>

int EditorObject::nextObjectId = 1;

EditorObject::EditorObject(GameObject *gameObject, int objectId) {
  heldObject = gameObject;
  if(objectId == 0) {
    this->objectId = nextObjectId;
    nextObjectId++;
  } else {
    this->objectId = objectId;
  }
}
