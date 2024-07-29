#include "PlayerManager.h"
#include "EntityManager.h"
#include "Vector2D.h"
#include "Components/Components.h"

Entity* PlayerManager::player = &EntityManager::CreatePlayer();

void PlayerManager::Spawn(Vector2D position)
{
    player->AddComponent<TransformComponent>(Vector2D(position), Vector2D(2, 2), Vector2D(0, 0), 3);
    player->AddComponent<SpriteComponent>("assets/player.png", 8, 8);
    player->AddComponent<KeyboardController>();
    player->AddComponent<ColliderComponent>(SDL_Rect {0, 0, 8, 8});
}
Entity* PlayerManager::GetPlayer()
{
    return player;
}
void PlayerManager::FireProjectile()
{
    Vector2D playerPosition = player->GetComponent<TransformComponent>().GetPosition();
    EntityManager::SpawnPlayerProjectile(playerPosition);
}

void PlayerManager::PlayerHit()
{
    
}
void PlayerManager::Update()
{
    
}
