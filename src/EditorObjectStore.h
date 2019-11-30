// -*- mode: c++ -*-

#ifndef EDITOR_OBJECT_STORE_H
#define EDITOR_OBJECT_STORE_H

#include <map>
#include "EditorObject.h"

class EditorObjectStore {
public:
  EditorObjectStore();
  int Add(EditorObject object);
  void Remove(int objectId);
  const EditorObject* GetObjectAt(int x, int y);

private:
  std::map<int, EditorObject> objects;
};

#endif
