#include "Meteorite.h"

Meteorite::Meteorite() : GameObject("meteorit1") {
  setBoundingRadius(60);
}

void Meteorite::update(float delta) {
  setPosition(x - 400*delta, y);
  if(x < -200) {
    x = 2000;
  }
}
