#pragma once

class Entity;

class TimerComponent : public Component {
public:
    TimerComponent(float t, void (*tExpired)(Entity*)) : timer(t * 1000), timeExpired(tExpired) {
        startTime = SDL_GetTicks();
    }

    void Update() override {
        if (SDL_GetTicks() - startTime > timer)
            timeExpired(entity);
    }
    
private:
    void (*timeExpired)(Entity*);
    Uint32 startTime;
    float timer;
};
