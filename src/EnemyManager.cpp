#include "EnemyManager.h"
#include "ECS/SystemManager.h"
#include "Components/Components.h"

void EnemyManager::SpawnEnemy(int enemyColumns, int enemyRows) {
    int columnSpace = Game::gameWidth / enemyColumns;
    totNumberOfEnemy = enemyColumns * enemyRows;
    
    for (int row = 0; row < enemyRows; row++) {
        for (int col = 0; col < enemyColumns; col++) {
            EntityManager::SpawnEnemy(Vector2D(col * columnSpace, row * Game::spriteSize), movingDirection);
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
        float currentEdge = static_cast<float>(Game::gameWidth - Game::spriteSize);
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
            enemyPosition->SetY(enemyPosition->GetPosition().y + static_cast<float>(Game::spriteSize));
            enemyPosition->SetVelocity(Vector2D(movingDirection, 0));
        }
    }
}
