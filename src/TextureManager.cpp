#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texturePath) {
    SDL_Surface* surface = IMG_Load(texturePath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect) {
    SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}
