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
    jumpAnimationTimer(0)
{
    playerIdle = {0};
    playerLeft = {0};
    playerRight = {0};
    playerJump = {0};
}

Player::~Player() {
    UnloadTexture(playerIdle);
    UnloadTexture(playerLeft);
    UnloadTexture(playerRight);
    UnloadTexture(playerJump);
}

void Player::LoadTextures() {
    playerIdle = LoadTexture("../assets/player/player_idle.png");
    playerLeft = LoadTexture("../assets/player/player_left.png");
    playerRight = LoadTexture("../assets/player/player_right.png");
    playerJump = LoadTexture("../assets/player/player_jump.png");
    
    playerIdle.width = width;
    playerIdle.height = height;
    playerLeft.width = width;
    playerLeft.height = height;
    playerRight.width = width;
    playerRight.height = height;
    playerJump.width = width;
    playerJump.height = height;
}
void Player::UnloadTextures() {
    UnloadTexture(playerIdle);
    UnloadTexture(playerLeft);
    UnloadTexture(playerJump);
    UnloadTexture(playerRight);
}

void Player::Update(std::vector<Rectangle>& platforms) {
    bool wasGroundedLastFrame = isGrounded;
    
    if (!isGrounded) {
        velocity.y += 0.5f;
    } else {
        velocity.y = 0;
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
            jumpAnimationTimer = jumpAnimationDelay;
        }
    }

    if (isJumping) {
        if (jumpAnimationTimer > 0) {
            jumpAnimationTimer--;
        } else {
            if (isGrounded) {
                isJumping = false;
            }
        }
    }

    position = newPosition;
}

void Player::Draw() const {
    if (isJumping) {
        DrawTexture(playerJump, position.x, position.y, WHITE);
    } 
    else if (wasMoving) {
        if (facingRight) {
            DrawTexture(playerRight, position.x, position.y, WHITE);
        } else {
            DrawTexture(playerLeft, position.x, position.y, WHITE);
        }
    }
    else {
        DrawTexture(playerIdle, position.x, position.y, WHITE);
    }
}

void Player::RewindTo(Vector2 newPosition) {
    position = newPosition;
    velocity = {0, 0};
}
