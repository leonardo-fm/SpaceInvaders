#include "EntityManager.h"
#include "Components/Components.h"

Entity& EntityManager::SpawnPlayer(int xPos, int yPos)
{
    Entity& player = Game::systemManager->CreateEntity(SystemManager::player);
    player.AddComponent<TransformComponent>(Vector2D(static_cast<float>(xPos), static_cast<float>(yPos)), Vector2D(2, 2), Vector2D(0, 0), 3);
    player.AddComponent<SpriteComponent>("assets/player.png", 8, 8);
    player.AddComponent<KeyboardController>();
    player.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 8, 8});

    return player;
}
Entity& EntityManager::SpawnPlayerProjectile(int xPos, int yPos)
{
    Entity& projectile = Game::systemManager->CreateEntity(SystemManager::playerProjectile);
    projectile.AddComponent<TransformComponent>(Vector2D(static_cast<float>(xPos), static_cast<float>(yPos)), Vector2D(1, 1), Vector2D(0, -1), 10);
    projectile.AddComponent<SpriteComponent>("assets/projectile.png", 2, 2);
    projectile.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 2, 2});

    return projectile;
}

Entity& EntityManager::SpawnEnemy(int xPos, int yPos, float movingDirection)
{
    Entity& enemy = Game::systemManager->CreateEntity(SystemManager::enemy);
    enemy.AddComponent<TransformComponent>(Vector2D(static_cast<float>(xPos), static_cast<float>(yPos)), Vector2D(4, 4), Vector2D(movingDirection, 0), 0.5);
    enemy.AddComponent<SpriteComponent>("assets/monster_1.png", 8, 8);
    enemy.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 8, 8});
    enemy.AddComponent<ShootComponent>();

    return enemy;
}
Entity& EntityManager::SpawnEnemyProjectile(int xPos, int yPos)
{
    Entity& projectile = Game::systemManager->CreateEntity(SystemManager::enemyProjectile);
    projectile.AddComponent<TransformComponent>(Vector2D(xPos, yPos), Vector2D(1, 5), Vector2D(0, 1), 2.5);
    projectile.AddComponent<SpriteComponent>("assets/projectile.png", 2, 2);
    projectile.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 2, 2});

    return projectile;
}
