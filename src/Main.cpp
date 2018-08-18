#include "Cats.h"
#include <SDL.h>
#include "Spaceship.h"
#include "Meteorite.h"

const int screenWidth = 1920;
const int screenHeight = 1080;

int main(int argc, char *argv[]) {
  float scale = 1.0f;
  if(argc > 1) {
    scale = std::stof(argv[1]);
  }

  SDL_Init(SDL_INIT_VIDEO);
  Cats::Init(screenWidth, screenHeight, scale);
  Cats::ShowPointer(false);
  Cats::LoadSprite("../data/gfx/rymdskepp.json");
  Cats::LoadSprite("../data/gfx/stor_eld.json");
  Cats::LoadSprite("../data/gfx/meteorit1.json");
  Cats::LoadTileset("../data/gfx/bakgrund1.json");
  Cats::SetupTileLayer(2, 1, screenWidth, screenHeight);

  for(int y = 0;y < 1;y++) {
    for(int x = 0;x < 2;x++) {
      Cats::SetTile(x, y, "bakgrund1", 0, 0);
    }
  }

  int lastFrameTime = SDL_GetTicks();
  bool running = true;
  SDL_Event event;

  Meteorite meteorite;
  Spaceship spaceship;
  float scroll = 0;

  spaceship.setPosition(screenWidth/2, screenHeight/2);
  meteorite.setPosition(screenWidth/2, screenHeight/2);
  float mouseX = 0, mouseY = 0;
  float dx = 0, dy = 0;

  while(running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        running = false;
      } else if(event.type == SDL_MOUSEMOTION) {
	mouseX = event.motion.x;
	mouseY = event.motion.y;
      } else if(event.type == SDL_KEYDOWN && event.key.repeat == 0) {
	switch(event.key.keysym.sym) {
	case SDLK_UP:    dy -= 1; break;
	case SDLK_DOWN:  dy += 1; break;
	case SDLK_LEFT:  dx -= 1; break;
	case SDLK_RIGHT: dx += 1; break;
	case SDLK_ESCAPE:
	  running = false;
	  break;
	}
      } else if(event.type == SDL_KEYUP) {
	switch(event.key.keysym.sym) {
	case SDLK_UP:
	  dy += 1;
	  break;
	case SDLK_DOWN:
	  dy -= 1;
	  break;
	case SDLK_LEFT:  dx += 1; break;
	case SDLK_RIGHT: dx -= 1; break;
	}
      }
    }

    spaceship.setDirection(dx, dy);
    //spaceship.moveToward(mouseX, mouseY);

    float delta = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    lastFrameTime = SDL_GetTicks();

    scroll -= delta * 150;
    while(scroll < -screenWidth) {
      scroll += screenWidth;
    }

    spaceship.update(delta);
    meteorite.update(delta);
    Cats::SetScroll((int)scroll, 0);

    if(spaceship.collides(meteorite)) {
      meteorite.setPosition(screenWidth, screenHeight/2);
    }

    Cats::Redraw(delta);
  }

  SDL_Quit();

  return 0;
}
