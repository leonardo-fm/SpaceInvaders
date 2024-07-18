#include "SystemManager.h"

Entity& SystemManager::CreateEntity() {
    Entity* entity = new Entity();
    entities.emplace_back(std::move(std::unique_ptr<Entity>{entity}));
    return *entity;
}
void SystemManager::RemoveEntity(Entity* entity) {
    auto newEnd = std::remove(entities.begin(), entities.end(), std::unique_ptr<Entity>{entity});
    entities.erase(newEnd, entities.end());
}

void SystemManager::Update() {
    for (auto& entety : entities) entety->Update();
}

void SystemManager::Draw() {
    for (auto& entety : entities) entety->Draw();
}
