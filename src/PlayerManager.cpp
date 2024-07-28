#include "PlayerManager.h"
#include "EntityManager.h"
#include "Vector2D.h"
#include "Components/TransformComponent.h"

void PlayerManager::Spawn(int xPos, int yPos)
{
    player = &EntityManager::SpawnPlayer(xPos, yPos);
}
void PlayerManager::FireProjectile()
{
    Vector2D playerPosition = player->GetComponent<TransformComponent>().GetPosition();
    EntityManager::SpawnPlayerProjectile(static_cast<int>(playerPosition.x), static_cast<int>(playerPosition.y));
}

void PlayerManager::PlayerHit()
{
    
}
void PlayerManager::Update()
{
    
}
