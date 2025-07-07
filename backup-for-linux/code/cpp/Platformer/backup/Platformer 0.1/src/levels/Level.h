#pragma once
#include "raylib.h"
#include <vector>

struct Platform {
    Rectangle rect;
    Color color;
};

class Level {
public:
    virtual void Load() = 0;
    virtual void Update();
    virtual void Draw();
    
    std::vector<Platform> platforms;
    Vector2 playerStartPosition { 100, 100 };
};