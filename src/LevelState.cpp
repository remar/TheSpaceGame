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

LevelState LevelState::instance;

void LevelState::EnterState() {
  spaceship = new Spaceship();

  std::string selected_file = ChooseFile();

  std::cout << "Selected file: " << selected_file << std::endl;

  LoadLevel("../data/levels/" + level);
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

  spaceship->setDirection(Input::instance.getDirection());

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

  char *jsontext = strdup(ReadFile(path).c_str());

  char *endptr;
  JsonValue value;
  JsonAllocator allocator;

  if(jsonParse(jsontext, &endptr, &value, allocator) != JSON_OK) {
    throw std::runtime_error("Unable to parse " + path);
  }

  JsonNode* node = value.toNode();

  if(strcmp(node->key, "objects") != 0) {
    throw std::runtime_error("Object doesn't have \"objects\" key! (" + path + ")");
  }

  value = node->value;

  // Loop through the objects in the array
  for(auto obj : value) {
    objectQueue.push_back(ReadObject(obj->value, path));
  }

  free(jsontext);

  objectQueue.sort();

  backgroundScroll = 0;
  levelScroll = 0;
  spaceship->setWorldPosition(screenWidth/2, screenHeight/2);
}


ObjectSpec LevelState::ReadObject(JsonValue value, std::string path) {
    bool gotX = false;
    int x = 0;
    bool gotY = false;
    int y = 0;
    bool gotType = false;
    ObjectType type = ObjectType::SMALL_ASTEROID;
    for(auto elm : value) {
      if(strcmp(elm->key, "x") == 0) {
	gotX = true;
	x = (elm->value).toNumber();
      } else if(strcmp(elm->key, "y") == 0) {
	gotY = true;
	y = (elm->value).toNumber();
      } else if(strcmp(elm->key, "type") == 0) {
	gotType = true;
	char *t = (elm->value).toString();
	if(strcmp(t, "small asteroid") == 0) {
	  type = ObjectType::SMALL_ASTEROID;
	} else if(strcmp(t, "medium asteroid") == 0) {
	  type = ObjectType::MEDIUM_ASTEROID;
	} else if(strcmp(t, "large asteroid") == 0) {
	  type = ObjectType::LARGE_ASTEROID;
	} else if(strcmp(t, "extra life") == 0) {
	  type = ObjectType::EXTRA_LIFE;
	}
      }
    }
    if(!gotX || !gotY || !gotType) {
      throw std::runtime_error("Incomplete object specification in " + path);
    }
    return ObjectSpec(x, y, type);
}

void LevelState::CreateAsteroidAt(float x, float y, ObjectType type) {
    Asteroid *asteroid = new Asteroid();
    asteroid->setWorldPosition(x, y);
    asteroids.push_back(asteroid);
}
