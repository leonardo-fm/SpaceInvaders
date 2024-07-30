#include "Debug.h"
#include "TextManager.h"

Debug::Debug() {
    textColor = {255, 255, 255, 255};
    fpsText = "-";
    fpsPosition = {0, 0, 0, 0};
    entityNumberPosition = {0, 15, 0, 0};
}

void Debug::StartFrame() {
    frames++;
    currentTime = SDL_GetTicks();
    if (pollingTime == 0) pollingTime = SDL_GetTicks();
}

void Debug::EndFrame() {
    renderTimeText = std::to_string(SDL_GetTicks() - currentTime);
    if (SDL_GetTicks() - pollingTime > 1000) {
        fpsText = std::to_string(frames);
        frameLastSecond = frames;
        frames = 0;
        pollingTime = 0;
    }
}

void Debug::Update() {
    fpsTexture = TextManager::LoadText(fpsText + "/" + renderTimeText + "ms", "assets/cour.ttf", 14, textColor);
    entityNumberTexture = TextManager::LoadText("entities: " + std::to_string(SystemManager::numberOfEntities), "assets/cour.ttf", 14, textColor);
}

void Debug::Draw() const {
    TextManager::Draw(fpsTexture, fpsPosition);
    TextManager::Draw(entityNumberTexture, entityNumberPosition);
}
