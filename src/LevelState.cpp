#include "LevelState.h"
#include "Constants.h"
#include "Input.h"
#include "Cats.h"

LevelState LevelState::instance;

void LevelState::EnterState() {
  backgroundScroll = 0;
  levelScroll = 0;
  spaceship = new Spaceship();
  spaceship->setPosition(screenWidth/2, screenHeight/2);
  for(int i = 0;i < 10;i++) {
    Asteroid *asteroid = new Asteroid();
    asteroid->setPosition(screenWidth + 200, i * (screenHeight/11) + screenHeight/11);
    asteroids.push_back(asteroid);
  }
}

void LevelState::ExitState() {
  delete spaceship;
  for(auto asteroid : asteroids) {
    delete asteroid;
  }
}

void LevelState::Update(GameLogic *gameLogic, float delta) {
    spaceship->setDirection(Input::Instance()->getDirection());

    backgroundScroll -= delta * 150;
    while(backgroundScroll < -screenWidth) {
      backgroundScroll += screenWidth;
    }

    spaceship->update(delta);
    for(auto a : asteroids) {
      if(a->collides(spaceship)) {
	a->setPosition(screenWidth + 200, a->getYPosition());
      }
      a->update(delta);
    }

    Cats::SetScroll((int)backgroundScroll, 0);
}
