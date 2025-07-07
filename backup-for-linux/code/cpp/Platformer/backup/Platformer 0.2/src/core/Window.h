#pragma once
#include "raylib.h"

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();
    
    bool shouldClose() const;
    void beginDrawing();
    void endDrawing();
    
private:
    int width;
    int height;
};