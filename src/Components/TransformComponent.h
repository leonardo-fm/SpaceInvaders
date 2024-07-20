#pragma once

#include "../Vector2D.h"
#include "../ECS/Component.h"
#include "Game.h"

class TransformComponent : public Component {
public:
    TransformComponent(Vector2D pos, Vector2D scl, Vector2D vel, int spd) {
        SetPosition(pos);
        SetScale(scl);
        SetVelocity(vel);
        speed = spd;
    }
    
    Vector2D GetPosition() const {
        return position;
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
    
    void Update() override {
        position.x += velocity.x * static_cast<float>(speed);
        position.y += velocity.y * static_cast<float>(speed);

        if (position.x > static_cast<float>(Game::gameWidth) || position.x < 0 ||
            position.y > static_cast<float>(Game::gameHeight) || position.y < 0) {
            entity->Destroy();
        }
    }
    
private:
    Vector2D position;
    Vector2D scale;
    Vector2D velocity;
    int speed;
};
