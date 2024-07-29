#pragma once
#include "EntityManager.h"

class EnemyManager {
public:
    void SpawnEnemy(int enemyColumns, int enemyRows);
    void StopEnemy();
    void Update();

private:
    float movingDirection = 1;
    int totNumberOfEnemy = 0;
};
