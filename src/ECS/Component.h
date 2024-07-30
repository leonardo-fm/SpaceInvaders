#pragma once

class Entity;

class Component {
public:
    Entity* entity;
    
    virtual ~Component() {}
    
    virtual void Init() {}
    virtual void Create() {}
    virtual void Update() {}
    virtual void Draw() {}
    virtual void Remove() {}

    virtual void Destroy() {}
};
