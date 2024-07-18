#pragma once

class Entity;

class Component {
public:
    Entity* entity;
    
    virtual ~Component() {}
    
    virtual void Init() {}
    virtual void Update() {}
    virtual void Draw() {}
};
