#include "EntityManager.h"
#include "Components/Components.h"

Entity& EntityManager::CreatePlayer() {
    Entity& player = Game::systemManager->CreateEntity(SystemManager::player);
    return player;
}

Entity& EntityManager::SpawnPlayerProjectile(Vector2D position) {
    Entity& projectile = Game::systemManager->CreateEntity(SystemManager::playerProjectile);
    projectile.AddComponent<TransformComponent>(Vector2D(position), Vector2D(4, 4), Vector2D(0, -1), 10);
    projectile.AddComponent<SpriteComponent>("assets/player_projectile.png", 1, 3);
    projectile.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 3, 3});
    projectile.AddComponent<DestroyComponent>();

    return projectile;
}

Entity& EntityManager::SpawnEnemy(Vector2D position, float movingDirection) {
    Entity& enemy = Game::systemManager->CreateEntity(SystemManager::enemy);
    enemy.AddComponent<TransformComponent>(Vector2D(position), Vector2D(4, 4), Vector2D(movingDirection, 0), 0.5);
    enemy.AddComponent<SpriteComponent>("assets/enemy.png", Game::spriteSize, Game::spriteSize);
    enemy.AddComponent<ColliderComponent>(SDL_Rect {0, 0, Game::spriteSize, Game::spriteSize});
    enemy.AddComponent<ShootComponent>();

    return enemy;
}

Entity& EntityManager::SpawnEnemyProjectile(Vector2D position) {
    Entity& projectile = Game::systemManager->CreateEntity(SystemManager::enemyProjectile);
    projectile.AddComponent<TransformComponent>(Vector2D(position), Vector2D(4, 4), Vector2D(0, 1), 2.5);
    projectile.AddComponent<SpriteComponent>("assets/enemy_projectile.png", 3, 3);
    projectile.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 3, 3});
    projectile.AddComponent<DestroyComponent>();

    return projectile;
}
