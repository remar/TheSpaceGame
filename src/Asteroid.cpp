#include "Asteroid.h"

Asteroid::Asteroid() : GameObject("asteroid1") {
  setBoundingRadius(185);
}

void Asteroid::update(float delta) {
  setPosition(x - 400*delta, y);
  if(x < -200) {
    x = 2000;
  }
}
