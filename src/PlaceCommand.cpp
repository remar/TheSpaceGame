#include "PlaceCommand.h"

#include "Asteroid.h"

PlaceCommand::PlaceCommand(EditorObjectStore &objects, ObjectType type, int x, int y)
  : objects(objects), type(type), x(x), y(y), objectId(0) { }

void PlaceCommand::Execute() {
  // Insert object into objects
  GameObject *go = new Asteroid();
  go->setWorldPosition(x, y);
  objectId = objects.Add(EditorObject(go, objectId));
}

void PlaceCommand::Unexecute() {
  // Delete object from objects
}
