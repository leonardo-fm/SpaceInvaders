#pragma once

#include "TransformComponent.h"
#include "../ECS/Entity.h"

class ColliderComponent : public Component {
public:
    ColliderComponent(SDL_Rect col) : collider(col) { }

    void Init() override {
        if (entity->HasComponent<TransformComponent>() == false) {
            std::cout << "Transform component not found" << '\n';
            Game::Stop();
        }
        transform = &entity->GetComponent<TransformComponent>();
        collider.w *= static_cast<int>(transform->GetScale().x);
        collider.h *= static_cast<int>(transform->GetScale().y);
    }
    
    void Update() override {
        Vector2D position = transform->GetPosition();
        collider.x = static_cast<int>(position.x);
        collider.y = static_cast<int>(position.y);
    }
    
    SDL_Rect GetCollider() const {
        return collider;    
    }
    
private:
    SDL_Rect collider;
    TransformComponent* transform;
};
