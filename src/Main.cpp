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
  Cats::LoadSprite("../data/gfx/buttons.json");
  Cats::LoadTileset("../data/gfx/bakgrund1.json");

  int lastFrameTime = SDL_GetTicks();
  bool running = true;

  GameLogic gameLogic;

  LevelState::instance.SetLevel("level.json");
  gameLogic.ChangeState(&LevelState::instance);

  while(running) {
    // Read input
    Input::instance.update();


    // Game logic
    running = !Input::instance.gotQuitEvent();

    float delta = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    lastFrameTime = SDL_GetTicks();

    gameLogic.Update(delta);


    // Render
    Cats::Redraw(delta);
  }

  SDL_Quit();

  return 0;
}
