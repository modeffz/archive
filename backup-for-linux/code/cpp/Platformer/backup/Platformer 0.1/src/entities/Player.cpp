#include "Player.h"
#include <algorithm> // для std::min

Player::Player() :
    position{100.0f, 100.0f},
    velocity{0.0f, 0.0f},
    width(50.0f),
    height(50.0f),
    isGrounded(false),
    color(GREEN),
    jumpGraceTimer(0),
    jumpGracePeriod(6)
{}

void Player::Update(std::vector<Rectangle>& platforms) {
    if (!isGrounded) {
        velocity.y += 0.5f;
    } else {
        velocity.y = 0;
    }

    velocity.y = std::min(velocity.y, 20.0f);

    velocity.x = IsKeyDown(KEY_A) ? -5.0f : IsKeyDown(KEY_D) ? 5.0f : 0.0f;

    Vector2 newPosition = {
        position.x + velocity.x,
        position.y + velocity.y
    };

    Rectangle playerRect = { newPosition.x, newPosition.y, width, height };
    bool wasGrounded = isGrounded;
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

    if (wasGrounded && !isGrounded && velocity.y >= 0) {
        if (jumpGraceTimer <= 0) jumpGraceTimer = jumpGracePeriod;
    }

    if (jumpGraceTimer > 0) jumpGraceTimer--;

    if (IsKeyPressed(KEY_SPACE)) {
        if (isGrounded || jumpGraceTimer > 0) {
            velocity.y = -12.6f;
            isGrounded = false;
            jumpGraceTimer = 0;
        }
    }

    position = newPosition;
}

void Player::Draw() const {
    DrawRectangleV(position, {width, height}, color);
}

void Player::RewindTo(Vector2 newPosition) {
    position = newPosition;
    velocity = {0, 0};
}