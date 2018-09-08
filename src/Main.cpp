#include "Cats.h"
#include <SDL2/SDL.h>
#include "Input.h"
#include "GameLogic.h"
#include "Constants.h"
#include "LevelState.h"

int main(int argc, char *argv[]) {
  float scale = 1.0f;
  if(argc > 1) {
    scale = std::stof(argv[1]);
  }

  SDL_Init(SDL_INIT_VIDEO);

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

  GameLogic gameLogic;

  gameLogic.ChangeState(LevelState::Instance());

  while(running) {
    // Read input
    Input::Instance()->update();


    // Game logic
    running = !Input::Instance()->gotQuitEvent();

    float delta = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    lastFrameTime = SDL_GetTicks();

    gameLogic.Update(delta);


    // Render
    Cats::Redraw(delta);
  }

  SDL_Quit();

  return 0;
}
