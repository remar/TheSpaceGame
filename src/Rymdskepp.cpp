#include "Rymdskepp.h"
#include "Cats.h"

Rymdskepp::Rymdskepp() : GameObject("rymdskepp") {
  eld = Cats::CreateSpriteInstance("stor_eld");
}

void Rymdskepp::update() {
  Cats::SetSpritePosition(eld, x - 60, y);
}
