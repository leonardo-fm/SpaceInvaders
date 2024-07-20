#include "EnemyManager.h"
#include "ECS/SystemManager.h"
#include "Components/Components.h"

int rowSpace = 32;;

void EnemyManager::Spawn(int enemyColumns, int enemyRows) {
    int columnSpace = Game::gameWidth / enemyColumns;
    totNumberOfEnemy = enemyColumns * enemyRows;
    
    for (int row = 0; row < enemyRows; row++) {
        for (int col = 0; col < enemyColumns; col++) {
            Entity& enemy = Game::systemManager->CreateEntity(SystemManager::enemy);
            Vector2D position = Vector2D(static_cast<float>(col * columnSpace), static_cast<float>(row * rowSpace));
            enemy.AddComponent<TransformComponent>(position, Vector2D(4, 4), Vector2D(movingDirection, 0), 0.5);
            enemy.AddComponent<SpriteComponent>("assets/monster_1.png", 8, 8);
            enemy.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 8, 8});
            enemy.AddComponent<ShootComponent>();
        }    
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
