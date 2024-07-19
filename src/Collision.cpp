﻿#include "Collision.h"

bool Collision::AABB(SDL_Rect rectA, SDL_Rect rectB) {
    if (rectA.x + rectA.w >= rectB.x &&
        rectB.x + rectB.w >= rectA.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.y + rectB.h >= rectA.y) {
        return true;
    }
    return false;
}
bool Collision::AABB(ColliderComponent colliderA, ColliderComponent colliderB) {
    return AABB(colliderA.GetCollider(), colliderB.GetCollider());
}
