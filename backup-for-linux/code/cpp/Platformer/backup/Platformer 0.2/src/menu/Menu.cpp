#include "Menu.h"


void Menu::Start() {
    float screenWidth  = GetRenderWidth();
    float screenHeight = GetRenderHeight();

    float rectWidth  = 200;
    float rectHeight = 100;

    Rectangle rect = {
        screenWidth / 2 - rectWidth / 2,
        screenHeight / 2 - rectHeight / 2,
        rectWidth,
        rectHeight
    };
    //Texture2D player = LoadTexture("../assets/player/1.png");
    //Vector2 playerPos = { 400, 300 };

    //DrawTexture(player, playerPos.x, playerPos.y, WHITE);
    DrawRectangleRec(rect, SKYBLUE);
}

/*void Menu::Unload() {
    UnloadTexture(player);
}*/
