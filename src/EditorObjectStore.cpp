#include "EditorObjectStore.h"

EditorObjectStore::EditorObjectStore() {
  
}

int EditorObjectStore::Add(EditorObject object) {
  objects.insert(std::pair<int,EditorObject>(object.objectId, object));
  return object.objectId;
}

void EditorObjectStore::Remove(int objectId) {
  objects[objectId].heldObject->destroy();
  objects.erase(objectId);
}

const EditorObject* EditorObjectStore::GetObjectAt(int x, int y) {
  for(auto const &object : objects) {
    if(object.second.heldObject->collides(x, y)) {
      return &object.second;
    }
  }

  return nullptr;
}
