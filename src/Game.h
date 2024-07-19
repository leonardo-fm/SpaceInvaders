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
    static SDL_Event event;
    
    void Init(const char* windowTitle, int width, int height);
    static bool IsRunning() { return running; }

    void HandleEvents();
    void Update();
    void Render();

    static void Stop();
    void Clean();
private:
    SDL_Window* window;
    static bool running;
};
