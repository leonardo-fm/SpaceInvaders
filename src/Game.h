#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "ECS/SystemManager.h"

class Game {
public:
    static int gameWidth;
    static int gameHeight;
    static SDL_Renderer* renderer;
    static SystemManager* systemManager;
    static SDL_Event event;
    
    void Init(const char* windowTitle, int width, int height);
    static bool IsRunning() { return running; }

    void StartFrame();
    void HandleEvents();
    void Update();
    void CollisionResolution();
    void Render();
    void EndFrame();

    static void Stop();
    void Clean();
    
private:
    SDL_Window* window;
    static bool running;
};
