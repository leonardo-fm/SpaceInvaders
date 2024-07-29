#pragma once

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
    std::vector<std::unique_ptr<Entity>>& GetEntityGroup(GameObjectsGroup group);
    
    void Refresh();
    void Create() const;
    void Update() const;
    void CollisionResolution();
    void Draw() const;
    
private:
    std::map<GameObjectsGroup, std::vector<std::unique_ptr<Entity>>> entitiesGroups;
};
