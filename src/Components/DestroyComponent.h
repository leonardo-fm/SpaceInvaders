#pragma once

class DestroyComponent : public Component {
public:
    void Update() override {
        Vector2D position = entity->GetComponent<TransformComponent>().GetPosition();
        SDL_Rect collider = entity->GetComponent<ColliderComponent>().GetCollider();
        if (position.x > static_cast<float>(Game::gameWidth) || position.x < -collider.w ||
            position.y > static_cast<float>(Game::gameHeight) || position.y < -collider.h) {
            entity->Destroy();
        }
    }
};
