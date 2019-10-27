#include "Input.h"
#include <map>

Input Input::instance;

typedef struct
{
  bool pressed; /* key pressed? */
  bool checked; /* key checked? */
} key_type;

std::map<int,key_type> keys;

Input::Input() : dx(0), dy(0), quitEvent(false) {}

void Input::update() {
  // iterate through events and keep track of appropriate stuff
  SDL_Event event;
  key_type key;
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

      key.pressed = true;
      key.checked = false;
      keys[event.key.keysym.sym] = key;
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

      key.pressed = false;
      key.checked = false;
      keys[event.key.keysym.sym] = key;
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

bool Input::pressed(int key) {
  if(keys[key].pressed && !keys[key].checked) {
    keys[key].checked = true;
    return true;
  }

  return false;
}
