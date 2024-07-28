#pragma once
#include "ECS/Entity.h"

class EntityManager
{
public:
    static Entity& SpawnPlayer(int xPos, int yPos);
    static Entity& SpawnPlayerProjectile(int xPos, int yPos);
    
    static Entity& SpawnEnemy(int xPos, int yPos, float movingDirection);
    static Entity& SpawnEnemyProjectile(int xPos, int yPos);
};
