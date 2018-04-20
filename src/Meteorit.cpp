#include "Meteorit.h"

Meteorit::Meteorit() : GameObject("meteorit1") {
  setBoundingRadius(60);
}

void Meteorit::update(float delta) {
  setPosition(x - 400*delta, y);
  if(x < -200) {
    x = 2000;
  }
}
