#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

class Game {
public:
    static SDL_Renderer* renderer;
    
    void Init(const char* windowTitle, int width, int height);
    bool IsRunning() { return running; }

    void HandleEvents();
    void Update();
    void Render();
    
    void Clean();
private:
    SDL_Window* window;
    bool running = false;
};
