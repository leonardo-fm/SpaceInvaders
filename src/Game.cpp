#include <iostream>

#include "Game.h"
#include "ECS/Entity.h"
#include "Components/Components.h"
#include "Debug.h"
#include "EnemyManager.h"
#include "PlayerManager.h"

int Game::gameWidth = 800;
int Game::gameHeight = 640;
int Game::spriteSize = 11;
int Game::spriteActualSize = 11 * 4;
bool Game::running = false;
float Game::deltaTime = 1;
Debug* debug;

PlayerManager* playerManager;
EnemyManager* enemyManager;

SDL_Renderer* Game::renderer = nullptr;
SystemManager* Game::systemManager = new SystemManager();
SDL_Event Game::event;

Game::Game(int bFPS, int cFPS) : baseFPS(bFPS), FPS(cFPS) {
    deltaTime = static_cast<float>(bFPS) / static_cast<float>(cFPS);
}

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

    enemyManager->SpawnEnemy(11, 5);
    playerManager->Spawn(Vector2D(static_cast<float>((gameWidth / 2) - (spriteActualSize / 2)), static_cast<float>(gameHeight - spriteActualSize)));
    
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
    if (debug->frameLastSecond != 0) {
        deltaTime = static_cast<float>(baseFPS) / static_cast<float>(debug->frameLastSecond);
    }
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
