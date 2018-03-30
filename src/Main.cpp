#include "Cats.h"
#include <SDL.h>

const int screenWidth = 1920;
const int screenHeight = 1080;

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  Cats::Init(screenWidth, screenHeight, 0.5f);
  Cats::ShowPointer(false);
  Cats::LoadSprite("../data/gfx/rymdskepp.json");
  Cats::LoadTileset("../data/gfx/bakgrund.json");
  Cats::SetupTileLayer(7, 4, 320, 320);

  for(int y = 0;y < 4;y++) {
    for(int x = 0;x < 7;x++) {
      Cats::SetTile(x, y, "bakgrund", 0, 0);
    }
  }

  int lastFrameTime = SDL_GetTicks();
  bool running = true;
  SDL_Event event;

  int rymdskepp = Cats::CreateSpriteInstance("rymdskepp");
  float scroll = 0;

  while(running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        running = false;
      } else if(event.type == SDL_MOUSEMOTION) {
	Cats::SetSpritePosition(rymdskepp, event.motion.x, event.motion.y);
      }
    }

    float delta = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    lastFrameTime = SDL_GetTicks();

    scroll -= delta * 50;
    while(scroll < -320) {
      scroll += 320;
    }

    Cats::SetScroll((int)scroll, 0);

    Cats::Redraw(delta);
  }

  SDL_Quit();

  return 0;
}
