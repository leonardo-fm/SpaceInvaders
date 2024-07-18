#pragma once

#include "../Vector2D.h"
#include "../ECS/Component.h"

class TransformComponent : public Component {
public:
    TransformComponent(int xPos, int yPos) {
        SetPosition(xPos, yPos);
    }
    Vector2D GetPosition() {
        return position;
    }
    void SetPosition(int x, int y) {
        position.x = static_cast<float>(x);
        position.y = static_cast<float>(y);
    }
private:
    Vector2D position;
};
