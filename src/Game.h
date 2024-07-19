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
    
    void Init(const char* windowTitle, int width, int height);
    bool IsRunning() { return running; }

    void HandleEvents();
    void Update();
    void Render();

    void Stop();
    void Clean();
private:
    SDL_Window* window;
    bool running = false;
};
