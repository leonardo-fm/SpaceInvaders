#pragma once

class EnemyManager {
public:
    void SpawnEnemy(int enemyColumns, int enemyRows);
    void StopEnemy();
    void Update();

private:
    float movingDirection = 1;
};
