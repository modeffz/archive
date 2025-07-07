#pragma once
#include "raylib.h"
#include <vector>

class Player {
public:
    Vector2 position;
    Vector2 velocity;
    float width;
    float height;
    bool isGrounded;
    Color color;

    Player();
    ~Player();
    void LoadTextures();
    void UnloadTextures();
    void Update(std::vector<Rectangle>& platforms);
    void Draw() const;
    void RewindTo(Vector2 newPosition);

private:
    int jumpGraceTimer;
    const int jumpGracePeriod;
    Texture2D playerIdle;
    Texture2D playerLeft;
    Texture2D playerRight;
    Texture2D playerJump;
    bool facingRight;
    bool wasMoving;
    bool isJumping;
    int jumpAnimationTimer;
    const int jumpAnimationDelay = 10;
};
