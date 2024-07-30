#pragma once

#include <SDL_render.h>

#include "TransformComponent.h"
#include "../ECS/Component.h"
#include "../TextureManager.h"

class SpriteAnimationComponent : public Component {
public:
    SpriteAnimationComponent(const char* texturePath, int w, int h, int frames, float animationTime) : framesNumber(frames), animationTimeBetweenFrames(animationTime * 1000) {
        texture = TextureManager::LoadTexture(texturePath);
        srcRect = {0, 0, w, h};
    }
    
    ~SpriteAnimationComponent() {
        SDL_DestroyTexture(texture);
    }

    void Init() override {
        if (entity->HasComponent<TransformComponent>() == false) {
            std::cout << "Transform component not found" << '\n';
            Game::Stop();
        }
        transform = &entity->GetComponent<TransformComponent>();
    }
    
    void Update() override {
        Vector2D position = transform->GetPosition();
        Vector2D scale = transform->GetScale();
        if (SDL_GetTicks() - lastFrameTime > animationTimeBetweenFrames) {
            lastFrameTime = SDL_GetTicks();
            srcRect.x = srcRect.w * frame++;
            frame %= framesNumber;
        }
        destRect = {static_cast<int>(position.x), static_cast<int>(position.y),
            srcRect.w * static_cast<int>(scale.x), srcRect.h * static_cast<int>(scale.y)};
    }
    
    void Draw() override {
        TextureManager::Draw(texture, srcRect, destRect);
    }

private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    int frame = 0;
    int framesNumber;
    float animationTimeBetweenFrames;
    Uint32 lastFrameTime = 0;
};
