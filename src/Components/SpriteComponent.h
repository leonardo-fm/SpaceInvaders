#pragma once

#include <SDL_render.h>

#include "../ECS/Component.h"
#include "../TextureManager.h"

class SpriteComponent : public Component {
public:
    SpriteComponent() = default;
    SpriteComponent(const char* texturePath, int x, int y, int w, int h) {
        texture = TextureManager::LoadTexture(texturePath);
        xPos = x;
        yPos = y;
        srcRect = {0, 0, w, h};
        destRect = {xPos, yPos, w, h};
    }
    ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }

    void Draw() override {
        TextureManager::Draw(texture, srcRect, destRect);
    }

private:
    int xPos;
    int yPos;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
};