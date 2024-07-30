#include "Debug.h"
#include "TextManager.h"

const char* font = "assets/cour.ttf";
const int fontSize = 14;

Debug::Debug() {
    textColor = {255, 255, 255, 255};
    fpsText = "-";
    fpsPosition = {0, 0, 0, 0};
    entityNumberPosition = {0, 15, 0, 0};
    deltaTimePosition = {0, 30, 0, 0};
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
    fpsTexture = TextManager::LoadText(fpsText + "/" + renderTimeText + "ms", font, fontSize, textColor);
    entityNumberTexture = TextManager::LoadText("entities: " + std::to_string(SystemManager::numberOfEntities), font, fontSize, textColor);
    deltaTimeTexture = TextManager::LoadText("delta time: " + std::to_string(Game::deltaTime), font, fontSize, textColor);
}

void Debug::Draw() const {
    TextManager::Draw(fpsTexture, fpsPosition);
    TextManager::Draw(entityNumberTexture, entityNumberPosition);
    TextManager::Draw(deltaTimeTexture, deltaTimePosition);
}
