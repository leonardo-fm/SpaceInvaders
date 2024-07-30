#include "EnemyManager.h"
#include "ECS/SystemManager.h"
#include "Components/Components.h"

void EnemyManager::SpawnEnemy(int enemyColumns, int enemyRows) {
    int offsetX = 100;
    int offsetY = 50;
    int columnSpace = (Game::gameWidth - (2 * offsetX)) / enemyColumns;
    int rowSpace = Game::spriteActualSize;
    totNumberOfEnemy = enemyColumns * enemyRows;

    int enemyType = 3;
    int drawRaws = enemyRows / enemyType;
    for (int row = 0; row < enemyRows; row++) {
        if (drawRaws-- == 0) {
            enemyType--;
            drawRaws = ((enemyRows - row) / enemyType) - 1;
        }
        
        for (int col = 0; col < enemyColumns; col++) {
            EntityManager::SpawnEnemy(Vector2D(col * columnSpace + offsetX, row * rowSpace + offsetY), movingDirection, enemyType);
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
        float currentEdge = static_cast<float>(Game::gameWidth - Game::spriteActualSize);
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
            enemyPosition->SetY(enemyPosition->GetPosition().y + static_cast<float>(Game::spriteActualSize));
            enemyPosition->SetVelocity(Vector2D(movingDirection, 0));
        }
    }
}
