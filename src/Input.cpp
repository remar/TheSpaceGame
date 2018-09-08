#include "Input.h"
#include <SDL2/SDL.h>

Input Input::instance;

Input::Input() : dx(0), dy(0), quitEvent(false) {}

void Input::update() {
  // iterate through events and keep track of appropriate stuff
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT) {
      quitEvent = true;
    } else if(event.type == SDL_KEYDOWN && event.key.repeat == 0) {
      switch(event.key.keysym.sym) {
      case SDLK_UP:    dy -= 1; break;
      case SDLK_DOWN:  dy += 1; break;
      case SDLK_LEFT:  dx -= 1; break;
      case SDLK_RIGHT: dx += 1; break;
      case SDLK_ESCAPE:
	// This makes Esc hard quit the game
	quitEvent = true;
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
}

Vector Input::getDirection() {
  Vector v;
  v.set(dx, dy);
  return v;
}

bool Input::gotQuitEvent() {
  return quitEvent;
}
