#include "SystemManager.h"

#include "../Collision.h"

int SystemManager::numberOfEntities = 0;

Entity& SystemManager::CreateEntity(GameObjectsGroup group) {
    Entity* entity = new Entity(*this);
    entitiesGroups[group].emplace_back(std::move(std::unique_ptr<Entity>{entity}));
    numberOfEntities++;
    return *entity;
}
std::vector<std::unique_ptr<Entity>>& SystemManager::GetEntityGroup(GameObjectsGroup group) {
    return entitiesGroups[group];
}

void SystemManager::Refresh() {
    for (auto& entitiesGroup : entitiesGroups) {
        entitiesGroup.second.erase(std::remove_if(entitiesGroup.second.begin(), entitiesGroup.second.end(),
        [](const std::unique_ptr<Entity> &entity) {
            if(entity->IsActive() == false) {
                numberOfEntities--;
                return true;
            }
            return false;
        }), entitiesGroup.second.end());
    }
}
void SystemManager::Create() {
    for (auto& entitiesGroup : entitiesGroups) {
        for (auto& entity : entitiesGroup.second) entity->Create();
    }
}
void SystemManager::Update() {
    for (auto& entitiesGroup : entitiesGroups) {
        for (auto& entity : entitiesGroup.second) entity->Update();
    }
}
void SystemManager::CollisionResolution() {
    // player projectiles
    for (auto& pp : entitiesGroups[playerProjectile]) {
        for (auto& e : entitiesGroups[enemy]) {
            if (Collision::AABB(pp->GetComponent<ColliderComponent>().GetCollider(), e->GetComponent<ColliderComponent>().GetCollider())) {
                pp->Destroy();
                e->Destroy();
            }
        }
    }

    // enemy projectiles
    for (auto& ep : entitiesGroups[enemyProjectile]) {
        for (auto& p : entitiesGroups[player]) {
            if (Collision::AABB(ep->GetComponent<ColliderComponent>().GetCollider(), p->GetComponent<ColliderComponent>().GetCollider())) {
                ep->Destroy();
                p->Destroy();
            }
        }
    }
}
void SystemManager::Draw() {
    for (auto& entitiesGroup : entitiesGroups) {
        for (auto& entity : entitiesGroup.second) entity->Draw();
    }
}
