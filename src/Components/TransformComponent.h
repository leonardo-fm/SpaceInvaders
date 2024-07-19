﻿#pragma once

#include "../Vector2D.h"
#include "../ECS/Component.h"

class TransformComponent : public Component {
public:
    TransformComponent(Vector2D pos, Vector2D vel) {
        SetPosition(pos);
        SetSpeed(vel);
    }
    
    Vector2D GetPosition() const {
        return position;
    }
    void SetPosition(Vector2D pos) {
        position = pos;
    }
    
    Vector2D GetSpeed() const {
        return velocity;
    }
    void SetSpeed(Vector2D vel) {
        velocity = vel;
    }
    
    void Update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
    
private:
    Vector2D position;
    Vector2D velocity;
    float speed = 1;
};
