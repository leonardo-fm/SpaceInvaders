#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    
    game = new Game();
    game->Init("Space invaders", Game::gameWidth, Game::gameHeight);

    while (game->IsRunning()) {
        frameStart = SDL_GetTicks();
        
        game->HandleEvents();
        game->Update();
        game->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    game->Clean();
    return 0;
}