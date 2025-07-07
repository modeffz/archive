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
    void Update(std::vector<Rectangle>& platforms);
    void Draw() const;
    void RewindTo(Vector2 newPosition);

private:
    int jumpGraceTimer;
    const int jumpGracePeriod;
};