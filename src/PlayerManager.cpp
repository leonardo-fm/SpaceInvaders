#include "PlayerManager.h"
#include "EntityManager.h"
#include "Vector2D.h"
#include "Components/Components.h"

Entity* PlayerManager::player = &EntityManager::CreatePlayer();
int PlayerManager::life = 1;

void PlayerManager::Spawn(Vector2D position) {
    player->AddComponent<TransformComponent>(Vector2D(position), Vector2D(2, 2), Vector2D(0, 0), 3);
    player->AddComponent<SpriteComponent>("assets/player.png", 8, 8);
    player->AddComponent<KeyboardController>();
    player->AddComponent<ColliderComponent>(SDL_Rect {0, 0, 8, 8});
    player->AddComponent<ScriptComponent>([]() {
        TransformComponent* transform = &player->GetComponent<TransformComponent>(); 
        Vector2D position = transform->GetPosition();
        if (position.x > Game::gameWidth - 2 || position.x < 2)
            transform->SetPosition(transform->GetLastPosition());
    });
}

void PlayerManager::FireProjectile() {
    Vector2D playerPosition = player->GetComponent<TransformComponent>().GetPosition();
    EntityManager::SpawnPlayerProjectile(playerPosition);
}

void PlayerManager::PlayerHit() {
    if (--life > 0)
    {
        player = &EntityManager::CreatePlayer();
        player->AddComponent<TransformComponent>(Vector2D(Game::gameWidth / 2, Game::gameHeight - 16), Vector2D(2, 2), Vector2D(0, 0), 3);
        player->AddComponent<SpriteComponent>("assets/player.png", 8, 8);
        player->AddComponent<KeyboardController>();
        player->AddComponent<ColliderComponent>(SDL_Rect {0, 0, 8, 8});
    } else {
        Game::EndGame(); 
    }
}

void PlayerManager::Update() {
    
}
