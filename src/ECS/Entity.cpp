#include "Entity.h"

#include "SystemManager.h"

Entity::Entity(SystemManager& manager) : systemManager(manager) { }

bool Entity::IsActive() {
    return active;
}

void Entity::Update() {
    for (auto& component : components) component->Update();
}
void Entity::Draw() {
    for (auto& component : components) component->Draw();
}
void Entity::Destroy() {
    active = false;
}
