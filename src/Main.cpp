#include "Cats.h"
#include <SDL.h>

const int screenWidth = 1920;
const int screenHeight = 1080;

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  Cats::Init(screenWidth, screenHeight, 0.5f);

  bool running = true;
  SDL_Event event;

  while(running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        running = false;
      }
    }

    Cats::Redraw(1);
  }

  SDL_Quit();

  return 0;
}
