﻿#pragma once

#include <array>
#include <bitset>
#include <memory>
#include <vector>

#include "Component.h"

constexpr size_t maxComponents = 32;

class SystemManager;

class Entity {
public:
    Entity(SystemManager& manager);
    bool IsActive();

    template<typename T, typename... TArgs> 
    T* AddComponent(TArgs&&... cArgs) {
        T* component = new T(std::forward<TArgs>(cArgs)...);
        components.emplace_back(std::move(std::unique_ptr<Component>{component}));
        component->entity = this;
        componentArray[GetComponentId<T>()] = component;
        componentBitset[GetComponentId<T>()] = true;
        component->Init();
        return component;
    }

    template <typename T>
    T& GetComponent() {
        return *static_cast<T*>(componentArray[GetComponentId<T>()]);
    }

    template <typename T>
    bool HasComponent() {
        return componentBitset[GetComponentId<T>()];
    }

    void Create();
    void Update();
    void Draw();
    void Destroy();
    
private:
    SystemManager& systemManager;
    bool active = true;
    
    std::array<Component*, maxComponents> componentArray;
    std::bitset<maxComponents> componentBitset;
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
