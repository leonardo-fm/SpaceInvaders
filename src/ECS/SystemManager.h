#pragma once

#include <memory>
#include <vector>

#include "Entity.h"

class SystemManager {
public:
    Entity& CreateEntity();
    void RemoveEntity(Entity* entity);

    void Update();
    void Draw();
    
private:
    std::vector<std::unique_ptr<Entity>> entities;
};
