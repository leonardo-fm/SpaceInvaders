#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

class Game {
public:
    void Init(const char* windowTitle, int width, int height);
    bool IsRunning() { return running; }
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running = false;
};
