#include "TimeRewind.h"

void TimeRewind::StartRecording(Player& player) {
    isRecording = true;
    positionHistory.clear();
    positionHistory.push_back(player.position);
}

void TimeRewind::StopRecording() {
    isRecording = false;
}

void TimeRewind::Update(Player& player) {
    if (IsKeyPressed(KEY_R)) {
        isRewinding = !isRewinding;
    }

    if (isRecording && !isRewinding) {
        positionHistory.push_back(player.position);
    }
}

void TimeRewind::Rewind(Player& player) {
    if (isRewinding && !positionHistory.empty()) {
        player.RewindTo(positionHistory.back());
        positionHistory.pop_back();
    }
}