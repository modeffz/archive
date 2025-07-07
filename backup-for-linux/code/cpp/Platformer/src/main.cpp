#include "raylib.h"
#include "entities/Player.h"
#include "utils/TimeRewind.h"
#include "levels/Level2.h"
#include "menu/Menu.h"
#include <vector>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Platformer Rewind");
    SetTargetFPS(60);

    Level2 level;
    level.Load();
    level.LoadTextures();
    
    Menu menu;

    Player player;
    player.position = level.playerStartPosition;
    player.LoadTextures();
    TimeRewind rewindSystem;
    rewindSystem.StartRecording(player);

    std::vector<Rectangle> platformRects;
    for (const auto& platform : level.platforms) {
        platformRects.push_back(platform.rect);
    }

    while (!WindowShouldClose()) {
       // if (!rewindSystem.IsRewinding()) {
            player.Update(platformRects);
        //}
        rewindSystem.Update(player);
        rewindSystem.Rewind(player);

        BeginDrawing();
            ClearBackground(BLACK);
            level.Draw();
            player.Draw();
            //menu.Draw();
            DrawText(TextFormat("Pos: %.0f, %.0f", player.position.x, player.position.y), 10, 10, 20, WHITE);
            DrawText(TextFormat("Rewind: %s", rewindSystem.IsRewinding() ? "ON" : "OFF"), 10, 30, 20, WHITE);
            DrawText("Controls: A/D - Move, SPACE - Jump, R - Rewind", 10, 570, 20, LIGHTGRAY);
        EndDrawing();

    }
    player.UnloadTextures();
    CloseWindow();
    return 0;
}
