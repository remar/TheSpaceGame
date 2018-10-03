#include "LevelState.h"
#include "Constants.h"
#include "Input.h"
#include "Cats.h"
#include <iostream>

LevelState LevelState::instance;

void LevelState::EnterState() {
  backgroundScroll = 0;
  levelScroll = 0;
  spaceship = new Spaceship();
  spaceship->setWorldPosition(screenWidth/2, 100);

  // Create dummy level
  for(int i = 0;i < 100;i++) {
    objectQueue.push_back(ObjectSpec(i*screenWidth/10, (i*screenHeight/10)%screenHeight, LARGE_ASTEROID));
  }
}

void LevelState::ExitState() {
  delete spaceship;
  for(auto asteroid : asteroids) {
    delete asteroid;
  }
}

void LevelState::Update(GameLogic *gameLogic, float delta) {
  // Spawn new objects
  while(!objectQueue.empty() && objectQueue.front().x < levelScroll + rightOfScreenOffset) {
    ObjectSpec spec = objectQueue.front();
    std::cout << "Spawning " << spec << std::endl;
    CreateAsteroidAt(spec.x, spec.y, spec.objectType);
    objectQueue.pop_front();
  }

  spaceship->setDirection(Input::Instance()->getDirection());

  // Gfx
  levelScroll += delta * 200;
  for(auto a : asteroids) {
    a->setCameraPosition(levelScroll, 0);
  }
  spaceship->setCameraPosition(levelScroll, 0);

  backgroundScroll -= delta * 150;
  while(backgroundScroll < -screenWidth) {
    backgroundScroll += screenWidth;
  }

  spaceship->update(delta);
  for(auto a : asteroids) {
    a->update(delta);
    if(a->collides(spaceship) || a->getWorldXPosition() < levelScroll + leftOfScreenOffset) {
      a->destroy();
    }
  }

  auto it = asteroids.begin();
  while(it != asteroids.end()) {
    if((*it)->isBeingDestroyed()) {
      it = asteroids.erase(it);
    } else {
      it++;
    }
  }

  Cats::SetScroll((int)backgroundScroll, 0);
}

void LevelState::CreateAsteroidAt(float x, float y, ObjectType type) {
    Asteroid *asteroid = new Asteroid();
    asteroid->setWorldPosition(x, y);
    asteroids.push_back(asteroid);
}
