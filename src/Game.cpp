#include "Game.h"
#include "TextureManager.h"

#include <iostream>

SDL_Renderer* Game::renderer = nullptr;

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

void Game::HandleEvents() {}
void Game::Update() {}
void Game::Render() {
    SDL_RenderClear(renderer);

    SDL_Texture* texture = TextureManager::LoadTexture("assets/monster_1.png");
    TextureManager::Draw(texture, {0, 0, 8, 8}, {0, 0, 16, 16});
    
    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned" << '\n';
}
