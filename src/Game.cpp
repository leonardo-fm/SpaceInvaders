#include "Game.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "ECS/Entity.h"
#include "Components/Components.h"

#include <iostream>


SystemManager systemManager;
SDL_Renderer* Game::renderer = nullptr;

Entity& enemy1 = systemManager.CreateEntity();
Entity& enemy2 = systemManager.CreateEntity();
Entity& enemy3 = systemManager.CreateEntity();

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
    
    enemy1.AddComponent<SpriteComponent>("assets/monster_1.png", 100, 100, 8, 8);
    enemy2.AddComponent<SpriteComponent>("assets/monster_1.png", 50, 100, 8, 8);
    enemy3.AddComponent<SpriteComponent>("assets/monster_1.png", 100, 50, 8, 8);
    
    running = true;
}

void Game::HandleEvents() {
    
}
void Game::Update() {
    systemManager.Update();
}
void Game::Render() {
    SDL_RenderClear(renderer);
    
    systemManager.Draw();
    
    SDL_Texture* textTexture = TextManager::LoadText("60", "assets/cour.ttf", 16, {255, 255, 255, 255});
    TextManager::Draw(textTexture, {0, 0, 0, 0});
    
    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned" << '\n';
}
