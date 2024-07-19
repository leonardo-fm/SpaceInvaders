#include "SystemManager.h"

int SystemManager::numberOfEntities = 0;

Entity& SystemManager::CreateEntity() {
    Entity* entity = new Entity(*this);
    entities.emplace_back(std::move(std::unique_ptr<Entity>{entity}));
    numberOfEntities++;
    return *entity;
}

void SystemManager::Refresh() {
    entities.erase(std::remove_if(entities.begin(), entities.end(),
        [](const std::unique_ptr<Entity> &entity) {
            if(entity->IsActive() == false) {
                numberOfEntities--;
                return true;
            }
            return false;
        }), entities.end());
}
void SystemManager::Update() {
    for (auto& entety : entities) entety->Update();
}
void SystemManager::Draw() {
    for (auto& entety : entities) entety->Draw();
}
