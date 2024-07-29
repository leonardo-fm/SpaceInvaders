#include "EnemyManager.h"
#include "ECS/SystemManager.h"
#include "Components/Components.h"

int rowSpace = 32;

void EnemyManager::SpawnEnemy(int enemyColumns, int enemyRows) {
    int columnSpace = Game::gameWidth / enemyColumns;
    totNumberOfEnemy = enemyColumns * enemyRows;
    
    for (int row = 0; row < enemyRows; row++) {
        for (int col = 0; col < enemyColumns; col++) {
            EntityManager::SpawnEnemy(Vector2D(col * columnSpace, row * rowSpace), movingDirection);
        }    
    }
}

void EnemyManager::StopEnemy() {
    for (auto& enemy : Game::systemManager->GetEntityGroup(SystemManager::enemy)) {
        enemy->GetComponent<ShootComponent>().Stop();
    }
}

void EnemyManager::Update() {
    // Check if go next row
    bool goNextRow = false;

    if (movingDirection == 1) {
        float currentEdge = static_cast<float>(Game::gameWidth - 16);
        for (auto& enemy : Game::systemManager->GetEntityGroup(SystemManager::enemy)) {
            if (enemy->GetComponent<TransformComponent>().GetPosition().x > currentEdge) {
                goNextRow = true;
                break;
            }
        }   
    } else {
        float currentEdge = 8;
        for (auto& enemy : Game::systemManager->GetEntityGroup(SystemManager::enemy)) {
            if (enemy->GetComponent<TransformComponent>().GetPosition().x < currentEdge) {
                goNextRow = true;
                break;
            }
        }   
    }

    if (goNextRow == false)
        return;
    
    // Move row
    movingDirection *= -1; // Invert direction
    auto& enemies = Game::systemManager->GetEntityGroup(SystemManager::enemy);
    for (auto& enemy : enemies) {
        if (enemy->IsActive()) {
            TransformComponent* enemyPosition = &enemy->GetComponent<TransformComponent>();
            enemyPosition->SetY(enemyPosition->GetPosition().y + static_cast<float>(rowSpace));
            enemyPosition->SetVelocity(Vector2D(movingDirection, 0));
        }
    }
}
