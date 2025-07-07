#include <raylib.h>

int main() {
    InitWindow(800, 600, "pos/size");
    SetTargetFPS(60);
    

    float posX = 100;
    float posY = 100;
    float rectWidth = 50;
    float rectHeight = 50;
    const float moveSpeed = 5.0f;
    const float resizeSpeed = 2.0f;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_A)) posX -= moveSpeed;
        if (IsKeyDown(KEY_D)) posX += moveSpeed;
        if (IsKeyDown(KEY_W)) posY -= moveSpeed;
        if (IsKeyDown(KEY_S)) posY += moveSpeed;
        if (IsKeyDown(KEY_LEFT)) rectWidth -= resizeSpeed;
        if (IsKeyDown(KEY_RIGHT)) rectWidth += resizeSpeed;
        if (IsKeyDown(KEY_UP)) rectHeight -= resizeSpeed;
        if (IsKeyDown(KEY_DOWN)) rectHeight += resizeSpeed;
        

        BeginDrawing();
        ClearBackground(BLACK);
        

        float drawWidth = rectWidth < 1 ? 1 : rectWidth;
        float drawHeight = rectHeight < 1 ? 1 : rectHeight;
        
        DrawRectangle(posX, posY, drawWidth, drawHeight, WHITE);
        DrawText(TextFormat("pos: %.1f, %.1f", posX, posY), 10, 10, 20, RED);
        DrawText(TextFormat("size: %.1f, %.1f", rectWidth, rectHeight), 10, 30, 20, RED);
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
