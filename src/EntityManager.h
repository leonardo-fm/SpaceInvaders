#pragma once
#include "Vector2D.h"
#include "ECS/Entity.h"

class EntityManager
{
public:
    static Entity& CreatePlayer();
    static Entity& SpawnPlayerProjectile(Vector2D position);
    
    static Entity& SpawnEnemy(Vector2D position, float movingDirection, int enemyType);
    static Entity& SpawnEnemyProjectile(Vector2D position);

    static Entity& SpawnExplosion(Vector2D position, Vector2D scale);
};
