#include "EntityManager.h"

#include <string>

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
    projectile.AddComponent<SoundComponent>(784, 100, true);

    return projectile;
}

Entity& EntityManager::SpawnEnemy(Vector2D position, float movingDirection, int enemyType) {
    Entity& enemy = Game::systemManager->CreateEntity(SystemManager::enemy);
    enemy.AddComponent<TransformComponent>(Vector2D(position), Vector2D(4, 4), Vector2D(movingDirection, 0), 0.1f);
    std::string enemyFileName;
    enemyFileName.append("assets/enemy_").append(std::to_string(enemyType)).append(".png");
    enemy.AddComponent<SpriteAnimationComponent>(enemyFileName.c_str(), Game::spriteSize, Game::spriteSize, 2, 1.0f);
    enemy.AddComponent<ColliderComponent>(SDL_Rect {0, 0, Game::spriteSize, Game::spriteSize});
    enemy.AddComponent<ShootComponent>();
    enemy.AddComponent<ExplosionComponent>();

    return enemy;
}

Entity& EntityManager::SpawnEnemyProjectile(Vector2D position) {
    Entity& projectile = Game::systemManager->CreateEntity(SystemManager::enemyProjectile);
    projectile.AddComponent<TransformComponent>(Vector2D(position), Vector2D(4, 4), Vector2D(0, 1), 2.5);
    projectile.AddComponent<SpriteAnimationComponent>("assets/enemy_projectile.png", 3, 3, 2, 0.2f);
    projectile.AddComponent<ColliderComponent>(SDL_Rect {0, 0, 3, 3});
    projectile.AddComponent<DestroyComponent>();
    projectile.AddComponent<ExplosionComponent>();
    projectile.AddComponent<SoundComponent>(98, 100, true);

    return projectile;
}

Entity& EntityManager::SpawnExplosion(Vector2D position, Vector2D scale) {
    Entity& explosion = Game::systemManager->CreateEntity(SystemManager::background);
    explosion.AddComponent<TransformComponent>(position, scale, Vector2D(0, 0), 0);
    explosion.AddComponent<SpriteComponent>("assets/explosion.png", Game::spriteSize, Game::spriteSize);
    explosion.AddComponent<TimerComponent>(0.05f, [](Entity* entity){ entity->Destroy(); });
       
    return explosion;
}
