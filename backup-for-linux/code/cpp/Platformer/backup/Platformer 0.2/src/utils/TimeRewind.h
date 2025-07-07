#pragma once
#include "raylib.h"
#include <vector>
#include "entities/Player.h"

class TimeRewind {
public:
    void StartRecording(Player& player);
    void StopRecording();
    void Update(Player& player);
    void Rewind(Player& player);
    
    bool IsRecording() const { return isRecording; }
    bool IsRewinding() const { return isRewinding; } 

private:
    bool isRecording = false;
    bool isRewinding = false;
    std::vector<Vector2> positionHistory;
};