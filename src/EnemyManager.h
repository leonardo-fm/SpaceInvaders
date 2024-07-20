#pragma once

#include <vector>

#include "Components/TransformComponent.h"

class EnemyManager {
public:
    void Spawn(int enemyColumns, int enemyRows);
    void Update();

private:
    float movingDirection = 1;
};
