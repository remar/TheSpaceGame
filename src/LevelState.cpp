#include "LevelState.h"
#include "Constants.h"
#include "Input.h"
#include "Cats.h"

LevelState LevelState::instance;

void LevelState::EnterState() {
  scroll = 0;
  spaceship = new Spaceship();
  asteroid = new Asteroid();
  spaceship->setPosition(screenWidth/2, screenHeight/2);
  asteroid->setPosition(screenWidth/2, screenHeight/2);
}

void LevelState::ExitState() {
  delete spaceship;
  delete asteroid;
}

void LevelState::Update(GameLogic *gameLogic, float delta) {
    spaceship->setDirection(Input::Instance()->getDirection());

    scroll -= delta * 150;
    while(scroll < -screenWidth) {
      scroll += screenWidth;
    }

    spaceship->update(delta);
    asteroid->update(delta);

    if(spaceship->collides(asteroid)) {
      asteroid->setPosition(screenWidth, screenHeight/2);
    }

    Cats::SetScroll((int)scroll, 0);
}

