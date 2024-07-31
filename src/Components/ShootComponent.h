#pragma once

#include "../ECS/Component.h"

class ShootComponent : public Component {
public:
    const int MaxTimeToWait = 20 * 1000;
    const int MinTimeToWait = 10 * 1000;
    
    void Init() override {
        lastShoot = SDL_GetTicks();
        msToWait = rand() % MaxTimeToWait;
    }
    
    void Create() override {
        if (stop) return;
        if (lastShoot + msToWait < SDL_GetTicks()) {
            Vector2D position = entity->GetComponent<TransformComponent>().GetPosition();
            EntityManager::SpawnEnemyProjectile(position);
            
            lastShoot = SDL_GetTicks();
            msToWait = rand() % MaxTimeToWait;
            msToWait = msToWait < MinTimeToWait ? MinTimeToWait : msToWait;
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
