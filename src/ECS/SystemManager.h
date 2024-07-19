﻿#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Entity.h"

class SystemManager {
public:
    enum GameObjectsGroup {
        background = 0,
        player = 1,
        enemy = 2,
        playerProjectile = 3,
        enemyProjectile = 4
    };
    
    static int numberOfEntities;
    Entity& CreateEntity(GameObjectsGroup group);

    void Refresh();
    void Update();
    void CollisionResolution();
    void Draw();
    
private:
    std::map<GameObjectsGroup, std::vector<std::unique_ptr<Entity>>> entitiesGroups;
};
