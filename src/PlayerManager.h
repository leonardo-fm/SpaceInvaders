#pragma once
#include "EntityManager.h"
#include "ECS/Entity.h"

class PlayerManager
{
public:
    void Spawn(int xPos, int yPos);
    void FireProjectile();
    void PlayerHit();
    void Update();

private:
    Entity* player; 
    int life = 1;
};
