#pragma once
#include <SDL.h>
#include <string>

class Debug {
public:
    Debug();
    void StartFrame();
    void EndFrame();

    void Update();
    void Draw() const;
    
private:
    SDL_Color textColor;
    
    std::string fpsText;
    std::string renderTimeText;
    SDL_Texture* fpsTexture;
    SDL_Rect fpsPosition;
    
    std::string entityNumberText;
    SDL_Texture* entityNumberTexture;
    SDL_Rect entityNumberPosition;

    Uint32 pollingTime = 0;
    Uint32 currentTime = 0;
    int frames;
};
