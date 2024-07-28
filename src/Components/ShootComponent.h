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
            Vector2D position = entity->GetComponent<TransformComponent>().GetPosition();
            EntityManager::SpawnEnemyProjectile(static_cast<int>(position.x), static_cast<int>( position.y));
            
            lastShoot = SDL_GetTicks();
            msToWait = rand() % 8000;
        }
    }
private:
    Uint32 lastShoot;
    int msToWait;
};
