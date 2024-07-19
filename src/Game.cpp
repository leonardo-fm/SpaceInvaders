#include "Game.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "ECS/Entity.h"
#include "Components/Components.h"
#include "Vector2D.h"

#include <iostream>

#include "Debug.h"
#include "Components/KeyboardController.h"


SystemManager systemManager;
int Game::gameWidth = 800;
int Game::gameHeight = 640;
bool Game::running = false;
Debug* debug;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Entity& player = systemManager.CreateEntity(SystemManager::player);

Entity& enemy = systemManager.CreateEntity(SystemManager::enemy);

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

    debug = new Debug();
    
    enemy.AddComponent<TransformComponent>(Vector2D(50, 200), Vector2D(0, 0));
    enemy.AddComponent<SpriteComponent>("assets/monster_1.png", 8, 8);
    enemy.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 8, 8});

    player.AddComponent<TransformComponent>(Vector2D(0, static_cast<float>(gameHeight - 8)), Vector2D(0, 0));
    player.AddComponent<SpriteComponent>("assets/player.png", 8, 8);
    player.AddComponent<KeyboardController>();
    
    running = true;
}

void Game::StartFrame() {
    debug->StartFrame();
    systemManager.Refresh();
}
void Game::EndFrame() {
    debug->EndFrame();
}

void Game::HandleEvents() {
    SDL_PollEvent(&event);
}
bool fire = false;
void Game::Update() {
    if (fire) {
        Entity& projectile = systemManager.CreateEntity(SystemManager::playerProjectile);
        projectile.AddComponent<TransformComponent>(player.GetComponent<TransformComponent>().GetPosition(), Vector2D(0, -10));
        projectile.AddComponent<SpriteComponent>("assets/projectile.png", 2, 2);
        projectile.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 2, 2});
        fire = false;
    }
    
    systemManager.Update();
    debug->Update();
}
void Game::CollisionResolution() {
    systemManager.CollisionResolution();
}
void Game::Render() {
    SDL_RenderClear(renderer);
    
    systemManager.Draw();
    debug->Draw();
    
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
void Game::FireProjectile() {
    fire = true;
}
