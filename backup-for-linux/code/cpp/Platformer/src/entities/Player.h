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
    void LoadTextures();
    void UnloadTextures();
    void Update(std::vector<Rectangle>& platforms);
    void Draw() const;
    void RewindTo(Vector2 newPosition);
    bool rewind = false;

private:
    int jumpGraceTimer;
    const int jumpGracePeriod;
    Texture2D playerIdle;
    Texture2D playerRunRight[4];
    Texture2D playerRunLeft[4];
    Texture2D playerJumpRight;
    Texture2D playerJumpLeft;
    Texture2D playerRewind[8];
    bool facingRight;
    bool wasMoving;
    bool isJumping;
    int animationTimer;
    const int animationDelay = 8;
    int currentFrame;
    int frameCount = 4;
    };
