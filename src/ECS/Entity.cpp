#include "Entity.h"

#include "SystemManager.h"

Entity::Entity(SystemManager& manager) : systemManager(manager) { }

bool Entity::IsActive() const {
    return active;
}

void Entity::Create() const {
    for (auto& component : components) component->Create();
}

void Entity::Update() const {
    for (auto& component : components) component->Update();
}

void Entity::Draw() const {
    for (auto& component : components) component->Draw();
}

void Entity::Destroy() {
    for (auto& component : components) component->Destroy();
    active = false;
}
