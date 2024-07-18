#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

    game = new Game();
    game->Init("Space invaders", 800, 640);

    while (game->IsRunning()) { }
    
    return 0;
}