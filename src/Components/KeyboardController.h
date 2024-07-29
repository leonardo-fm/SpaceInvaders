#pragma once

#include "../ECS/Component.h"
#include "TransformComponent.h"
#include "../Game.h"
#include "../PlayerManager.h"

class KeyboardController : public Component {
public:
    void Init() override {
        if (entity->HasComponent<TransformComponent>() == false) {
            std::cout << "Transform component not found" << '\n';
            Game::Stop();
        }
        transform = &entity->GetComponent<TransformComponent>();
    }
    
    void Update() override {
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
            case SDLK_LEFT:
                transform->SetVelocity(Vector2D(-1, 0));
                break;
            case SDLK_RIGHT:
                transform->SetVelocity(Vector2D(1, 0));
                break;
            case SDLK_SPACE:
                if (hasShoot) return;
                PlayerManager::FireProjectile();
                hasShoot = true;
                shootTime = SDL_GetTicks();
                break;
            default:
                break;
            }
        }
        
        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_RIGHT:
                transform->SetVelocity(Vector2D(0, 0));
                break;
            default:
                break;
            }
        }

        if (SDL_GetTicks() - shootTime > shootDelay)
            hasShoot = false;
    }
private:
    TransformComponent* transform = nullptr;
    bool hasShoot = false;
    Uint32 shootTime = 0;
    Uint32 shootDelay = 500;
};
