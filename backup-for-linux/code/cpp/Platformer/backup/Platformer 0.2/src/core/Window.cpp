#include "Window.h"

Window::Window(int width, int height, const char* title) 
    : width(width), height(height) {
    InitWindow(width, height, title);
    SetTargetFPS(60);
}

Window::~Window() {
    CloseWindow();
}

bool Window::shouldClose() const {
    return WindowShouldClose();
}

void Window::beginDrawing() {
    BeginDrawing();
    ClearBackground(BLACK);
}

void Window::endDrawing() {
    EndDrawing();
}