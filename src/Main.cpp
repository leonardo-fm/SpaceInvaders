#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

    game = new Game();
    game->Init("Space invaders", 800, 640);

    while (game->IsRunning()) {
        game->HandleEvents();
        game->Update();
        game->Render();
    }

    game->Clean();
    return 0;
}