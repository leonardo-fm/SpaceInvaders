#pragma once

#include <array>
#include <memory>
#include <vector>

#include "Component.h"

constexpr size_t maxComponents = 32;

class Entity {
public:
    Entity();

    template<typename T, typename... TArgs> 
    void AddComponent(TArgs&&... cArgs) {
        T* component = new T(std::forward<TArgs>(cArgs)...);
        components.emplace_back(std::move(std::unique_ptr<Component>{component}));
        componentArray[GetComponentId<T>()] = component;
    }

    template <typename T>
    Component* GetComponent() {
        return componentArray[GetComponentId<T>()];
    }
    
    void Update();
    void Draw();
    
private:
    std::array<Component*, maxComponents> componentArray;
    std::vector<std::unique_ptr<Component>> components;

    size_t GetNewComponentId() {
        static size_t lastId = 0;
        return lastId++;
    }

    template <typename T>
    size_t GetComponentId() {
        static size_t typeId = GetNewComponentId();
        return typeId;
    }
};
