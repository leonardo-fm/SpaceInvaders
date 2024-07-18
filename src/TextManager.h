#pragma once

#include <string>

#include "Game.h"

class TextManager {
public:
    static SDL_Texture* LoadText(std::string text, const char* fontPath, int fontSize, SDL_Color textColor);
    static void Draw(SDL_Texture* textTexture, SDL_Rect destRect);
};
