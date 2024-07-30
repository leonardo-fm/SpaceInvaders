#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "ECS/SystemManager.h"

class Game {
public:
    static int gameWidth;
    static int gameHeight;
    static int spriteSize;
    static SDL_Renderer* renderer;
    static SystemManager* systemManager;
    static SDL_Event event;
    static float deltaTime;

    Game(int bFPS, int cFPS);
    
    void Init(const char* windowTitle, int width, int height);
    static bool IsRunning() { return running; }

    void StartFrame();
    void HandleEvents();
    void Update();
    void CollisionResolution();
    void Render();
    void EndFrame();

    static void EndGame();
    static void Stop();
    void Clean();
    
private:
    int baseFPS;
    int FPS;
    SDL_Window* window;
    static bool running;
};
