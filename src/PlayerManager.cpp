#include "PlayerManager.h"
#include "EntityManager.h"
#include "Vector2D.h"
#include "Components/Components.h"

#include <vector>

Entity* PlayerManager::player = &EntityManager::CreatePlayer();
int PlayerManager::live = 3;
std::vector<Entity*> lives;
Vector2D spawnPoint;

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
    
    player->AddComponent<TransformComponent>(Vector2D(position), Vector2D(4, 4), Vector2D(0, 0), 3);
    player->AddComponent<SpriteComponent>("assets/player.png", Game::spriteSize, Game::spriteSize);
    player->AddComponent<KeyboardController>();
    player->AddComponent<ColliderComponent>(SDL_Rect {0, 0, Game::spriteSize, Game::spriteSize});
    player->AddComponent<ScriptComponent>([]() {
        TransformComponent* transform = &player->GetComponent<TransformComponent>(); 
        Vector2D position = transform->GetPosition();
        if (position.x > Game::gameWidth || position.x < 0)
            transform->SetPosition(transform->GetLastPosition());
    });
}

void PlayerManager::FireProjectile() {
    Vector2D playerPosition = player->GetComponent<TransformComponent>().GetPosition();
    EntityManager::SpawnPlayerProjectile(Vector2D(playerPosition.x + Game::spriteActualSize / 2 - 2, playerPosition.y));
}

void PlayerManager::PlayerHit() {
    if (--live > 0)
    {
        player = &EntityManager::CreatePlayer();
        player->AddComponent<TransformComponent>(spawnPoint, Vector2D(4, 4), Vector2D(0, 0), 3);
        player->AddComponent<SpriteComponent>("assets/player.png", Game::spriteSize, Game::spriteSize);
        player->AddComponent<KeyboardController>();
        player->AddComponent<ColliderComponent>(SDL_Rect {0, 0, Game::spriteSize, Game::spriteSize});
        player->AddComponent<ScriptComponent>([]() {
            TransformComponent* transform = &player->GetComponent<TransformComponent>(); 
            Vector2D position = transform->GetPosition();
            if (position.x > Game::gameWidth || position.x < 0)
                transform->SetPosition(transform->GetLastPosition());
        });
    } else {
        Game::EndGame(); 
    }
    
    lives[live]->Destroy();
}
