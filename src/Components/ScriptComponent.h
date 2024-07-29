#pragma once

#include "../ECS/Component.h"

class ScriptComponent : public Component {
public:
    ScriptComponent(void (*func)()) : sFunc(func) { }

    void Update() override {
        sFunc();
    }
    
private:
    void (*sFunc)();
};
