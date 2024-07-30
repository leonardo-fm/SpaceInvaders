#pragma once
#include "EntityManager.h"
#include "ECS/Entity.h"

class PlayerManager
{
public:
    PlayerManager();
    static Entity* player;
    
    void Spawn(Vector2D position);
    static void FireProjectile();
    static void PlayerHit();

private:
    static int live;
};
