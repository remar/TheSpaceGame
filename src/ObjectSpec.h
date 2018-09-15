// -*- mode: c++ -*-

#ifndef OBJECT_SPEC_H
#define OBJECT_SPEC_H

#include <iostream>

class ObjectSpec {
public:
  float x, y;
  ObjectSpec(float x, float y) : x(x), y(y) {}
  bool operator <(const ObjectSpec &spec) { return x < spec.x; }
};

std::ostream& operator<<(std::ostream &str, const ObjectSpec &spec);

#endif
