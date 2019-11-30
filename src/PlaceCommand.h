// -*- mode: c++ -*-

#ifndef PLACE_COMMAND_H
#define PLACE_COMMAND_H

#include "Command.h"
#include <list>
#include "EditorObjectStore.h"
#include "ObjectSpec.h"

class PlaceCommand : public Command {
public:
  PlaceCommand(EditorObjectStore &objects, ObjectType type, int x, int y);
  virtual void Execute();
  virtual void Unexecute();

private:
  EditorObjectStore &objects;
  ObjectType type;
  int x;
  int y;
  int objectId;
};

#endif
