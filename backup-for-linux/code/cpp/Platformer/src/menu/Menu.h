#pragma once
#include <raylib.h>
#include <vector>
#include "entities/Player.h"
#include "levels/Level2.h"

class Menu {
    public:
        void LoadTextures();
        void UnloadTextures();
        bool isStarting = false;
        bool closeSig = false;
        void Draw(Player& player, Level2& level);
        bool IsStartButtonPressed();
        bool IsExitButtonPressed();
        
    private:
        Vector2 getMousePos;
        Texture2D startButton[2];
        Texture2D exitButton[2];
};

