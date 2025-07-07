#include "Level.h"

void Level::Update() {

}

void Level::Draw() {
    for (const auto& platform : platforms) {
        DrawRectangleRec(platform.rect, platform.color);
    }
}