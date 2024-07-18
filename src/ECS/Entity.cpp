#include "Entity.h"

Entity::Entity() {}

void Entity::Update() {
    for (auto& component : components) component->Update();
}

void Entity::Draw() {
    for (auto& component : components) component->Draw();
}
