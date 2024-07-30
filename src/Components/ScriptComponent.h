#pragma once

#include "../ECS/Component.h"

class ScriptComponent : public Component {
public:
    ScriptComponent(void (*func)(Entity*)) : sFunc(func) { }

    void Update() override {
        sFunc(entity);
    }
    
private:
    void (*sFunc)(Entity*);
};
