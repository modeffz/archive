#include "TimeRewind.h"

void TimeRewind::StartRecording(Player& player) {
    isRecording = true;
    isRewinding = false;
    positionHistory.clear();
    lastRecordTime = GetTime();
    positionHistory.emplace_back(player.position, lastRecordTime);
}

void TimeRewind::StopRecording() {
    isRecording = false;
}

void TimeRewind::Update(Player& player) {
    float currentTime = GetTime();
    
    if (IsKeyPressed(KEY_R)) {
        if (!isRewinding && isRecording) {
            isRewinding = true;
            player.rewind = true;
            CleanOldRecords();
        } else {
            isRewinding = false;
            player.rewind = false;
        }
    }

    if (isRecording && !isRewinding && currentTime - lastRecordTime >= 0.005f) {
        positionHistory.emplace_back(player.position, currentTime);
        lastRecordTime = currentTime;
        CleanOldRecords();
    }
}

void TimeRewind::Rewind(Player& player) {
    if (isRewinding && !positionHistory.empty()) {
        player.RewindTo(positionHistory.back().first);
        positionHistory.pop_back();
        
        if (positionHistory.empty()) {
            isRewinding = false;
            player.rewind = false;
        }
    }
}

void TimeRewind::CleanOldRecords() {
    float currentTime = GetTime();
    while (!positionHistory.empty() && currentTime - positionHistory.front().second > rewindDuration) {
        positionHistory.erase(positionHistory.begin());
    }
}
