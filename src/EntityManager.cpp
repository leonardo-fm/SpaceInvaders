#include "EntityManager.h"
#include "Components/Components.h"

Entity& EntityManager::CreatePlayer() {
    Entity& player = Game::systemManager->CreateEntity(SystemManager::player);
    return player;
}

Entity& EntityManager::SpawnPlayerProjectile(Vector2D position) {
    Entity& projectile = Game::systemManager->CreateEntity(SystemManager::playerProjectile);
    projectile.AddComponent<TransformComponent>(Vector2D(position), Vector2D(1, 1), Vector2D(0, -1), 10);
    projectile.AddComponent<SpriteComponent>("assets/projectile.png", 2, 2);
    projectile.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 2, 2});

    return projectile;
}

Entity& EntityManager::SpawnEnemy(Vector2D position, float movingDirection) {
    Entity& enemy = Game::systemManager->CreateEntity(SystemManager::enemy);
    enemy.AddComponent<TransformComponent>(Vector2D(position), Vector2D(4, 4), Vector2D(movingDirection, 0), 0.5);
    enemy.AddComponent<SpriteComponent>("assets/monster_1.png", 8, 8);
    enemy.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 8, 8});
    enemy.AddComponent<ShootComponent>();

    return enemy;
}

Entity& EntityManager::SpawnEnemyProjectile(Vector2D position) {
    Entity& projectile = Game::systemManager->CreateEntity(SystemManager::enemyProjectile);
    projectile.AddComponent<TransformComponent>(Vector2D(position), Vector2D(1, 5), Vector2D(0, 1), 2.5);
    projectile.AddComponent<SpriteComponent>("assets/projectile.png", 2, 2);
    projectile.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 2, 2});

    return projectile;
}
