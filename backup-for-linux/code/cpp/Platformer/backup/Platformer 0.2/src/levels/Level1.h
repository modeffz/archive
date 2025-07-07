#pragma once
#include "Level.h"

class Level1 : public Level {
public:
    void Load() override {
        platforms = {
            { { 0, 550, 800, 50 }, GREEN },    
            { { 300, 400, 200, 20 }, BLUE },   
            { { 100, 300, 150, 20 }, RED },   
            { { 500, 250, 100, 20 }, GRAY }   
        };
        
        playerStartPosition = { 100, 100 };
    }
};
