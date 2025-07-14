#include"Menu.h"

void Menu::UnloadTextures() {
    for (int i=0; i<2; ++i) {
        UnloadTexture(startButton[i]);
        UnloadTexture(exitButton[i]);
    }
} 

void Menu::Draw(Player& player, Level2& level) {
    float rectWidth  = 200;
    float rectHeight = 75;
    float screenWidth  = GetRenderWidth() / 2 - rectWidth / 2;
    float screenHeight = GetRenderHeight() / 2 - rectHeight / 2;
    getMousePos = GetMousePosition();

    Rectangle rect = {
        screenWidth,
        screenHeight,
        rectWidth,
        rectHeight
    };
    
    Rectangle rect2= {
        screenWidth,
        screenHeight + 70,
        rectWidth,
        rectHeight
    };

    Vector2 pos = {
        screenWidth,
        screenHeight
    };

    if (!isStarting) {
        DrawTexture(level.sky, 0, 0, WHITE);
        if (CheckCollisionPointRec(getMousePos, rect)) {
            DrawTexture(startButton[1], screenWidth, screenHeight, WHITE);
        } else {
            DrawTexture(startButton[0], screenWidth, screenHeight, WHITE);
        }
        if (CheckCollisionPointRec(getMousePos, rect2)) {
            DrawTexture(exitButton[1], screenWidth, screenHeight + 65, WHITE);
        } else {
            DrawTexture(exitButton[0], screenWidth, screenHeight + 65, WHITE);
        }


        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(getMousePos, rect)) {
                isStarting = true;
            } else if (CheckCollisionPointRec(getMousePos, rect2)) {
                closeSig = true;
            }
        }
    } else {
        level.Draw();
        player.Draw();
    }
}

bool Menu::IsStartButtonPressed() {
    return isStarting;
}

bool Menu::IsExitButtonPressed() {
    return closeSig;
}

void Menu::LoadTextures() {
    for (int i=0; i < 2; ++i) {
        startButton[i] = LoadTexture(TextFormat("../assets/menu/start_%d.png", i + 1));
        exitButton[i] = LoadTexture(TextFormat("../assets/menu/exit_%d.png", i + 1));
    }
}
