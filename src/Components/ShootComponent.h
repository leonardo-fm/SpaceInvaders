#pragma once

#include "../ECS/Component.h"

class ShootComponent : public Component {
public:
    void Init() override {
        lastShoot = SDL_GetTicks();
        msToWait = rand() % 8000;
    }
    void Create() override {
        if (lastShoot + msToWait < SDL_GetTicks()) {
            Entity& projectile = Game::systemManager->CreateEntity(SystemManager::enemyProjectile);
            projectile.AddComponent<TransformComponent>(entity->GetComponent<TransformComponent>().GetPosition(), Vector2D(1, 5), Vector2D(0, 1), 2.5);
            projectile.AddComponent<SpriteComponent>("assets/projectile.png", 2, 2);
            projectile.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 2, 2});

            lastShoot = SDL_GetTicks();
            msToWait = rand() % 8000;
        }
    }
private:
    Uint32 lastShoot;
    int msToWait;
};
