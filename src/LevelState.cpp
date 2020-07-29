#include "LevelState.h"
#include "Constants.h"
#include "Input.h"
#include "Cats.h"
#include <iostream>
#include <string>
#include "Util.h"
#include <cstring>
#include <SDL2/SDL.h>
#include <string.h>
#include "FileDialog.h"
#include "EditorState.h"
#include "pugixml.hpp"

LevelState LevelState::instance;

using std::string;
using std::cout;

void LevelState::EnterState() {
  spaceship = new Spaceship();

  Cats::SetupTileLayer(2, 1, screenWidth, screenHeight);

  for(int y = 0;y < 1;y++) {
    for(int x = 0;x < 2;x++) {
      Cats::SetTile(x, y, "bakgrund1", 0, 0);
    }
  }

  LoadLevel("../data/levels/" + level);

  StartLevel();
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

  if(Input::instance.pressed(SDLK_e)) {
    gameLogic->ChangeState(&EditorState::instance);
    return;
  }

  spaceship->setDirection(Input::instance.getDirection());

  // Gfx
  levelScroll += delta * 200;
  SetCameraPosition(levelScroll, 0);

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
      std::cout << "Destroying object" << std::endl;
      it = asteroids.erase(it);
    } else {
      it++;
    }
  }

  Cats::SetScroll((int)backgroundScroll, 0);
}

void LevelState::LoadLevel(std::string path) {
  std::cout << "Loading level \"" << path << "\"" << std::endl;

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(path.c_str());

  if(!result) {
    throw std::runtime_error("Unable to open " + path);
  }

  originalObjectQueue.clear();
  for(auto obj : doc.child("map").child("objectgroup").children("object")) {
    int gid = obj.attribute("gid").as_int();

    // TODO: Base offset on some kind of table instead, this is a hack
    int offset = (3 - gid)*100;

    int x = obj.attribute("x").as_int() + offset;
    // origin is lower left corner for objects... hence the weird math
    int y = obj.attribute("y").as_int() - offset;
    cout << gid << "," << x << "," << y << ",offset:" << offset << std::endl;
    originalObjectQueue.push_back(ObjectSpec(x, y, ObjectType::LARGE_ASTEROID));
  }
  originalObjectQueue.sort();
}

void LevelState::StartLevel() {
  objectQueue = originalObjectQueue;
  backgroundScroll = 0;
  levelScroll = 0;
  spaceship->setWorldPosition(screenWidth/2, screenHeight/2);
  spaceship->show(true);
}

void LevelState::CreateAsteroidAt(float x, float y, ObjectType type) {
    Asteroid *asteroid = new Asteroid();
    asteroid->setWorldPosition(x, y);
    asteroids.push_back(asteroid);
}

void LevelState::SetCameraPosition(float x, float y) {
    for(auto a : asteroids) {
      a->setCameraPosition(x, y);
    }
    spaceship->setCameraPosition(x, y);
}
