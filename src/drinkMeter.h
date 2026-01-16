#pragma once

class DrinkMeter {
    public:
        float sipSize;
        float currentLevel = 1.0f;
        
        void sip();
        void reset();

        void draw();
};