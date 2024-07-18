#pragma once

#include <SDL_render.h>

#include "TransformComponent.h"
#include "../ECS/Component.h"
#include "../TextureManager.h"

class SpriteComponent : public Component {
public:
    SpriteComponent(const char* texturePath, int x, int y, int w, int h) {
        texture = TextureManager::LoadTexture(texturePath);
        xPos = x;
        yPos = y;
        srcRect = {0, 0, w, h};
    }
    ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }

    void Init() override {
        if (entity->HasComponent<TransformComponent>() == false) {
            std::cout << "Transform component not found" << '\n';
            return;
        }
        Vector2D position = entity->GetComponent<TransformComponent>().GetPosition();
        destRect = {static_cast<int>(position.x), static_cast<int>(position.y), srcRect.w, srcRect.h};
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