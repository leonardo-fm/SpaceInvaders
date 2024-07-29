#pragma once

#include "../Vector2D.h"
#include "../ECS/Component.h"
#include "Game.h"

class TransformComponent : public Component {
public:
    TransformComponent(Vector2D pos, Vector2D scl, Vector2D vel, float spd) {
        SetPosition(pos);
        SetScale(scl);
        SetVelocity(vel);
        speed = spd;
    }
    
    Vector2D GetPosition() const {
        return position;
    }
    Vector2D GetLastPosition() const {
        return lastPosition;
    }
    void SetPosition(Vector2D pos) {
        position = pos;
    }
    void SetX(float x) {
        position.x = x;
    }
    void SetY(float y) {
        position.y = y;
    }
    
    Vector2D GetScale() const {
        return scale;
    }
    void SetScale(Vector2D scl) {
        scale = scl;
    }

    Vector2D GetVelocity() const {
        return velocity;
    }
    void SetVelocity(Vector2D vel) {
        velocity = vel;
    }

    float GetSpeed() const {
        return speed;
    }
    void SetSpeed(float spd) {
        speed = spd;
    }
    
    void Update() override {
        lastPosition = position;
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;

        if (position.x > static_cast<float>(Game::gameWidth) || position.x < 0 ||
            position.y > static_cast<float>(Game::gameHeight) || position.y < 0) {
            entity->Destroy();
        }
    }
    
private:
    Vector2D position;
    Vector2D lastPosition;
    Vector2D scale;
    Vector2D velocity;
    float speed;
};
