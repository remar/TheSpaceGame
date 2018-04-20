#include "Rymdskepp.h"
#include "Cats.h"

Rymdskepp::Rymdskepp() : GameObject("rymdskepp") {
  eld = Cats::CreateSpriteInstance("stor_eld");
  setBoundingRadius(40);
}

void Rymdskepp::update(float delta) {
  Cats::SetSpritePosition(eld, x - 60, y);
}
