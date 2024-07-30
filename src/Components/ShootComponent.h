#pragma once

#include "../ECS/Component.h"

class ShootComponent : public Component {
public:
    void Init() override {
        lastShoot = SDL_GetTicks();
        msToWait = rand() % 50000;
    }
    
    void Create() override {
        if (stop) return;
        if (lastShoot + msToWait < SDL_GetTicks()) {
            Vector2D position = entity->GetComponent<TransformComponent>().GetPosition();
            EntityManager::SpawnEnemyProjectile(position);
            
            lastShoot = SDL_GetTicks();
            msToWait = rand() % 8000;
        }
    }
    
    void Stop() {
        stop = true;
    }
private:
    Uint32 lastShoot = 0;
    int msToWait = 0;
    bool stop = false;
};
