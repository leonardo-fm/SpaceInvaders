#pragma once

#include <SDL_rect.h>

#include "Components/ColliderComponent.h"

class Collision {
public:
    bool AABB(SDL_Rect rectA, SDL_Rect rectB);
    bool AABB(ColliderComponent colliderA, ColliderComponent colliderB);
};
