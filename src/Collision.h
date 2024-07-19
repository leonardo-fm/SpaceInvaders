#pragma once

#include <SDL_rect.h>

#include "Components/ColliderComponent.h"

class Collision {
public:
    static bool AABB(SDL_Rect rectA, SDL_Rect rectB);
    static bool AABB(ColliderComponent colliderA, ColliderComponent colliderB);
};
