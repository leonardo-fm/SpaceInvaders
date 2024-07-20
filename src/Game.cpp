#include "Game.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "ECS/Entity.h"
#include "Components/Components.h"
#include "Vector2D.h"

#include <iostream>

#include "Debug.h"
#include "EnemyManager.h"
#include "Components/KeyboardController.h"


int Game::gameWidth = 800;
int Game::gameHeight = 640;
bool Game::running = false;
Debug* debug;
EnemyManager* enemyManager;

SDL_Renderer* Game::renderer = nullptr;
SystemManager* Game::systemManager = new SystemManager();
SDL_Event Game::event;

Entity& player = Game::systemManager->CreateEntity(SystemManager::player);

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
    enemyManager = new EnemyManager();

    enemyManager->Spawn(10, 10);
    
    player.AddComponent<TransformComponent>(Vector2D(0, static_cast<float>(gameHeight - 16)), Vector2D(2, 2), Vector2D(0, 0), 3);
    player.AddComponent<SpriteComponent>("assets/player.png", 8, 8);
    player.AddComponent<KeyboardController>();
    
    running = true;
}

void Game::StartFrame() {
    debug->StartFrame();
    systemManager->Refresh();
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
        Entity& projectile = systemManager->CreateEntity(SystemManager::playerProjectile);
        projectile.AddComponent<TransformComponent>(player.GetComponent<TransformComponent>().GetPosition(), Vector2D(1, 1), Vector2D(0, -1), 10);
        projectile.AddComponent<SpriteComponent>("assets/projectile.png", 2, 2);
        projectile.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 2, 2});
        fire = false;
    }

    enemyManager->Update();
    systemManager->Update();
    debug->Update();
}
void Game::CollisionResolution() {
    systemManager->CollisionResolution();
}
void Game::Render() {
    SDL_RenderClear(renderer);
    
    systemManager->Draw();
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
