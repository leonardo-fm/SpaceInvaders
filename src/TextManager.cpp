#include "TextManager.h"

SDL_Texture* TextManager::LoadText(std::string text, const char* fontPath, int fontSize, SDL_Color textColor) {
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void TextManager::Draw(SDL_Texture* textTexture, SDL_Rect destRect) {
    SDL_QueryTexture(textTexture, nullptr, nullptr, &destRect.w, &destRect.h);
    SDL_RenderCopy(Game::renderer, textTexture, nullptr, &destRect);
}
