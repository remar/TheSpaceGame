// -*- mode: c++ -*-

#ifndef OBJECT_SPEC_H
#define OBJECT_SPEC_H

#include <iostream>

enum ObjectType {
  SMALL_ASTEROID,
  MEDIUM_ASTEROID,
  LARGE_ASTEROID,
  EXTRA_LIFE
};

class ObjectSpec {
public:
  float x, y;
  ObjectType objectType;

  ObjectSpec(float x, float y, ObjectType objectType) : x(x), y(y), objectType(objectType) {}
  bool operator <(const ObjectSpec &spec) { return x < spec.x; }
};

std::ostream& operator<<(std::ostream &str, const ObjectSpec &spec);

#endif
