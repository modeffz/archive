#include "Player.h"
#include <algorithm>

Player::Player() :
    position{100.0f, 100.0f},
    velocity{0.0f, 0.0f},
    width(32.0f),
    height(60.0f),
    isGrounded(false),
    color(GREEN),
    jumpGraceTimer(0),
    jumpGracePeriod(6),
    facingRight(true),
    wasMoving(false),
    isJumping(false),
    animationTimer(0),
    currentFrame(0)
{
    playerIdle = {0};
    for (int i = 0; i < 4; ++i) {
        playerRunRight[i] = {0};
        playerRunLeft[i] = {0};
    }
    for (int i = 0; i < 8; ++i) {
        playerRewind[i] = {0};
    }
    playerJumpRight = {0};
    playerJumpLeft = {0};
}

void Player::LoadTextures() {
    playerIdle = LoadTexture("../assets/player/player_idle.png");
    for (int i = 0; i < 4; ++i) {
        playerRunRight[i] = LoadTexture(TextFormat("../assets/player/player_run_right_%d.png", i + 1));
        playerRunLeft[i] = LoadTexture(TextFormat("../assets/player/player_run_left_%d.png", i + 1));
    }
    for (int i = 0; i < 8; ++i) {
        playerRewind[i] = LoadTexture(TextFormat("../assets/player/player_rewind_%d.png", i + 1));
    }
    playerJumpRight = LoadTexture("../assets/player/player_jump_right.png");
    playerJumpLeft = LoadTexture("../assets/player/player_jump_left.png");
    
    playerIdle.width = width;
    playerIdle.height = height;
    for (int i = 0; i < 4; ++i) {
        playerRunRight[i].width = width;
        playerRunRight[i].height = height;
        playerRunLeft[i].width = width;
        playerRunLeft[i].height = height;
    }
    for (int i = 0; i < 8; ++i) {
        playerRewind[i].width = width;
        playerRewind[i].height = height;
    }
    playerJumpRight.width = width;
    playerJumpRight.height = height;
    playerJumpLeft.width = width;
    playerJumpLeft.height = height;
}

void Player::UnloadTextures() {
    UnloadTexture(playerIdle);
    for (int i = 0; i < 4; ++i) {
        UnloadTexture(playerRunRight[i]);
        UnloadTexture(playerRunLeft[i]);
    }
    for (int i = 0; i < 8; ++i) {
        UnloadTexture(playerRewind[i]);
    }
    UnloadTexture(playerJumpRight);
    UnloadTexture(playerJumpLeft);
}

void Player::Update(std::vector<Rectangle>& platforms) {
    bool wasGroundedLastFrame = isGrounded;
    
    if (!isGrounded) {
        velocity.y += 0.5f;
    } else {
        velocity.y = 0;
        isJumping = false;
    }

    if (rewind) {
        frameCount = 8;

    } else {
        frameCount = 4;

    }

    velocity.y = std::min(velocity.y, 20.0f);
    velocity.x = IsKeyDown(KEY_A) ? -5.0f : IsKeyDown(KEY_D) ? 5.0f : 0.0f;
    
    if (velocity.x > 0) {
        facingRight = true;
        wasMoving = true;
    } else if (velocity.x < 0) {
        facingRight = false;
        wasMoving = true;
    } else {
        wasMoving = false;
    }

    if (wasMoving && !isJumping || rewind) {
        if (animationTimer <= 0) {
            currentFrame = (currentFrame + 1) % frameCount;
            animationTimer = animationDelay;
        } else {
            animationTimer--;
        }
    } else if (!isJumping) {
        currentFrame = 0;
    }
    
    Vector2 newPosition = {
        position.x + velocity.x,
        position.y + velocity.y
    };

    Rectangle playerRect = { newPosition.x, newPosition.y, width, height };
    isGrounded = false;

    for (auto& platform : platforms) {
        if (CheckCollisionRecs(playerRect, platform)) {
            if (velocity.y > 0 && position.y + height <= platform.y) {
                newPosition.y = platform.y - height;
                velocity.y = 0;
                isGrounded = true;
                jumpGraceTimer = jumpGracePeriod;
            }
            else if (velocity.y < 0 && position.y >= platform.y + platform.height) {
                newPosition.y = platform.y + platform.height;
                velocity.y = 0;
            }
            else {
                if (velocity.x > 0) {
                    newPosition.x = platform.x - width;
                } else if (velocity.x < 0) {
                    newPosition.x = platform.x + platform.width;
                }
                velocity.x = 0;
            }
        }
    }

    if (IsKeyPressed(KEY_SPACE)) {
        if (isGrounded || jumpGraceTimer > 0) {
            velocity.y = -12.6f;
            isGrounded = false;
            jumpGraceTimer = 0;
            isJumping = true;
        }
    }
    position = newPosition;
}

void Player::Draw() const {
    if (isJumping && !rewind) {
        if (facingRight) {
            DrawTexture(playerJumpRight, position.x, position.y, WHITE);
        } else {
            DrawTexture(playerJumpLeft, position.x, position.y, WHITE);
        }
    } else if (wasMoving && !rewind) {
        if (facingRight) {
            DrawTexture(playerRunRight[currentFrame], position.x, position.y, WHITE);
        } else {
            DrawTexture(playerRunLeft[currentFrame], position.x, position.y, WHITE);
        }
    } else if (rewind) {
            DrawTexture(playerRewind[currentFrame], position.x, position.y, WHITE);
    } else {
        DrawTexture(playerIdle, position.x, position.y, WHITE);
    }
}

void Player::RewindTo(Vector2 newPosition) {
    position = newPosition;
    isJumping = false;
    wasMoving = true;
    frameCount = 8; 

}
