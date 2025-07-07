#include "Menu.h"


void Menu::Draw() {
    float rectWidth  = 200;
    float rectHeight = 100;
    float screenWidth  = GetRenderWidth() / 2 - rectWidth / 2;
    float screenHeight = GetRenderHeight() / 2 - rectHeight / 2;


    Rectangle rect = {
        screenWidth,
        screenHeight,
        rectWidth,
        rectHeight
    };
  
    DrawRectangleRec(rect, SKYBLUE);
    DrawText(TextFormat("start"),screenWidth, screenHeight, 3, WHITE);
}


