#pragma once
#include "EntityManager.h"
#include "ECS/Entity.h"

class PlayerManager
{
public:
    static Entity* player;
    
    void Spawn(Vector2D position);
    Entity* GetPlayer();
    static void FireProjectile();
    static void PlayerHit();
    void Update();

private:
    int life = 1;
};
