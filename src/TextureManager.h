#pragma once

#include "Game.h"

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* texturePath);
    static void Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
};
