#pragma once

#include "../ECS/Component.h"

class ExplosionComponent : public Component {
public:
    void Destroy() override {
        TransformComponent* transform = &entity->GetComponent<TransformComponent>();
        ColliderComponent* collider = &entity->GetComponent<ColliderComponent>();
        Vector2D scale = transform->GetScale();
        float maxValue = std::max(collider->GetCollider().w / scale.x, collider->GetCollider().h / scale.y);
        scale *= Vector2D(maxValue / Game::spriteSize, maxValue / Game::spriteSize);
        EntityManager::SpawnExplosion(transform->GetPosition(), scale);
    }
};
