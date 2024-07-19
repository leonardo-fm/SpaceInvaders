#pragma once

#include <memory>
#include <vector>

#include "Entity.h"

class SystemManager {
public:
    static int numberOfEntities;
    Entity& CreateEntity();

    void Refresh();
    void Update();
    void Draw();
    
private:
    std::vector<std::unique_ptr<Entity>> entities;
};
