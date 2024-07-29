#pragma once
#include "Vector2D.h"
#include "ECS/Entity.h"

class EntityManager
{
public:
    static Entity& CreatePlayer();
    static Entity& SpawnPlayerProjectile(Vector2D position);
    
    static Entity& SpawnEnemy(Vector2D position, float movingDirection);
    static Entity& SpawnEnemyProjectile(Vector2D position);
};
