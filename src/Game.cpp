#include <iostream>

#include "Game.h"
#include "TextManager.h"
#include "ECS/Entity.h"
#include "Components/Components.h"
#include "Debug.h"
#include "EnemyManager.h"
#include "PlayerManager.h"

int Game::gameWidth = 800;
int Game::gameHeight = 640;
bool Game::running = false;
Debug* debug;

PlayerManager* playerManager;
EnemyManager* enemyManager;

SDL_Renderer* Game::renderer = nullptr;
SystemManager* Game::systemManager = new SystemManager();
SDL_Event Game::event;

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
    playerManager = new PlayerManager();

    enemyManager->SpawnEnemy(10, 5);
    playerManager->Spawn(Vector2D(gameWidth / 2, gameHeight - 16));
    
    running = true;
}

void Game::StartFrame() {
    debug->StartFrame();
}
void Game::HandleEvents() {
    SDL_PollEvent(&event);

    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            Stop();
            break;
        default:
            break;
        }
    } else if (event.type == SDL_WINDOWEVENT) {
        switch (event.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
            std::cout << "Hi!";
            Stop();
            break;
        default:
            break;
        }
    }
}

void Game::Update() {
    systemManager->Refresh();
    // entity refresh()
    systemManager->Create(); // NO
    // entity manager create()
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
void Game::EndFrame() {
    debug->EndFrame();
}

void Game::EndGame() {
    enemyManager->StopEnemy();
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
