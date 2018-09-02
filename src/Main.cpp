#include "Cats.h"
#include <SDL2/SDL.h>
#include "Spaceship.h"
#include "Asteroid.h"
#include "Input.h"

const int screenWidth = 1920;
const int screenHeight = 1080;

int main(int argc, char *argv[]) {
  float scale = 1.0f;
  if(argc > 1) {
    scale = std::stof(argv[1]);
  }

  SDL_Init(SDL_INIT_VIDEO);

  Input input;

  Cats::Init(screenWidth, screenHeight, scale);
  Cats::ShowPointer(false);

  // Read in resources
  Cats::LoadSprite("../data/gfx/rymdskepp.json");
  Cats::LoadSprite("../data/gfx/stor_eld.json");
  Cats::LoadSprite("../data/gfx/asteroid1.json");
  Cats::LoadTileset("../data/gfx/bakgrund1.json");

  Cats::SetupTileLayer(2, 1, screenWidth, screenHeight);

  for(int y = 0;y < 1;y++) {
    for(int x = 0;x < 2;x++) {
      Cats::SetTile(x, y, "bakgrund1", 0, 0);
    }
  }

  int lastFrameTime = SDL_GetTicks();
  bool running = true;

  Asteroid asteroid;
  Spaceship spaceship;
  float scroll = 0;

  spaceship.setPosition(screenWidth/2, screenHeight/2);
  asteroid.setPosition(screenWidth/2, screenHeight/2);

  while(running) {
    // Read input
    input.update();


    // Game logic
    running = !input.gotQuitEvent();

    spaceship.setDirection(input.getDirection());

    float delta = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    lastFrameTime = SDL_GetTicks();

    scroll -= delta * 150;
    while(scroll < -screenWidth) {
      scroll += screenWidth;
    }

    spaceship.update(delta);
    asteroid.update(delta);

    if(spaceship.collides(asteroid)) {
      asteroid.setPosition(screenWidth, screenHeight/2);
    }

    Cats::SetScroll((int)scroll, 0);


    // Render
    Cats::Redraw(delta);
  }

  SDL_Quit();

  return 0;
}
