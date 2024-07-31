#pragma once

#include "../ECS/Component.h"

#include <windows.h>
#include <thread>

class SoundComponent : public Component {
public:
    SoundComponent(int freq, int milliSec, bool playNow) : frequency(freq), time(milliSec) {
        if (playNow) Play();   
    }
    
    void Play() {
        std::thread soundThread([this]() {
            Beep(frequency, time);
        });
        soundThread.detach();
    }
    
private:
    int frequency;
    int time;
};
