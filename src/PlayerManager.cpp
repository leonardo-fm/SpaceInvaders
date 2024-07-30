#include "PlayerManager.h"
#include "EntityManager.h"
#include "Vector2D.h"
#include "Components/Components.h"

#include <vector>

Entity* PlayerManager::player;
int PlayerManager::live = 3;
std::vector<Entity*> lives;
Vector2D spawnPoint;

void (*CheckBoundaries)(Entity*) = [](Entity* entity) {
    TransformComponent* transform = &entity->GetComponent<TransformComponent>(); 
    Vector2D position = transform->GetPosition();
    if (position.x + Game::spriteActualSize > Game::gameWidth || position.x < 0)
        transform->SetPosition(transform->GetLastPosition());
};

PlayerManager::PlayerManager() {
    for (int i = 0; i < live; i++) {
        Entity* lifeImage = &Game::systemManager->CreateEntity(SystemManager::background);
        lifeImage->AddComponent<TransformComponent>(Vector2D(Game::gameWidth - (i + 1) * Game::spriteSize - 8, 8), Vector2D(1, 1), Vector2D(0, 0), 0);
        lifeImage->AddComponent<SpriteComponent>("assets/player.png", Game::spriteSize, Game::spriteSize);
        lives.push_back(lifeImage);
    }
}

void PlayerManager::Spawn(Vector2D position) {
    spawnPoint = position;
    player = &EntityManager::CreatePlayer();
    player->AddComponent<TransformComponent>(spawnPoint, Vector2D(4, 4), Vector2D(0, 0), 3);
    player->AddComponent<SpriteComponent>("assets/player.png", Game::spriteSize, Game::spriteSize);
    player->AddComponent<KeyboardController>();
    player->AddComponent<ColliderComponent>(SDL_Rect {0, 0, Game::spriteSize, Game::spriteSize});
    player->AddComponent<ScriptComponent>(CheckBoundaries);
}

void PlayerManager::FireProjectile() {
    Vector2D playerPosition = player->GetComponent<TransformComponent>().GetPosition();
    EntityManager::SpawnPlayerProjectile(Vector2D(playerPosition.x + Game::spriteActualSize / 2 - 2, playerPosition.y));
}

void PlayerManager::PlayerHit() {
    if (--live > 0)
    {
        Spawn(spawnPoint);
        
        for (auto& projectile : Game::systemManager->GetEntityGroup(SystemManager::enemyProjectile)) {
            projectile->Destroy();
        }
    } else {
        Game::EndGame(); 
    }
    
    lives[live]->Destroy();
}
