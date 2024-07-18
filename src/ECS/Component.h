#pragma once

class Component {
public:
    virtual ~Component() {}
    
    virtual void Init() {}
    virtual void Update() {}
    virtual void Draw() {}
};
