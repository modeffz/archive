#include "Level.h"

void Level::UnloadTextures() {
    UnloadTexture(sky);
}

void Level::Update() {

}

void Level::LoadTextures() {
    sky = LoadTexture("../assets/sky/sky_2.png");
}

void Level::Draw() {
    DrawTexture(sky, 0, 0, WHITE);
    for (const auto& platform : platforms) {
        DrawRectangleRec(platform.rect, platform.color);
    }
}
