#include "Game.h"

#include <iostream>

void Game::Init(const char* windowTitle, int width, int height) {

    // Init window
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, NULL);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    } else {
        std::cout << "Error: Init() SDL" << '\n';
        return;
    }

    // Init text
    if (TTF_Init() == -1) {
        std::cout << "Error: Init() SDL_TTF" << '\n';
    }

    running = true;
}
