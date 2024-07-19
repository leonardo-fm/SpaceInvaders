#include "Game.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "ECS/Entity.h"
#include "Components/Components.h"
#include "Vector2D.h"

#include <iostream>


SystemManager systemManager;
int Game::gameWidth = 800;
int Game::gameHeight = 640;
SDL_Renderer* Game::renderer = nullptr;

Entity& player = systemManager.CreateEntity();

Entity& enemy1 = systemManager.CreateEntity();

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
    
    enemy1.AddComponent<TransformComponent>(Vector2D(50, 200), Vector2D(1, 1));
    enemy1.AddComponent<SpriteComponent>("assets/monster_1.png", 8, 8);

    player.AddComponent<TransformComponent>(Vector2D(0, static_cast<float>(gameHeight - 8)), Vector2D(1, 0));
    player.AddComponent<SpriteComponent>("assets/player.png", 8, 8);
    
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

void Game::Stop() {
    running = false;
}

void Game::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned" << '\n';
}
