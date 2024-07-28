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
                EntityManager::SpawnPlayerProjectile(1, 1);
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
            case SDLK_ESCAPE:
                Game::Stop();
                break;
            default:
                break;
            }
        }
    }
private:
    TransformComponent* transform;
};
