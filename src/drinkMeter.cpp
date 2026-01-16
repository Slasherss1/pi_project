#include "drinkMeter.h"
#include <raylib.h>

void DrinkMeter::sip() {
    currentLevel -= sipSize;
    if (currentLevel < 0.0f) {
        currentLevel = 0.0f;
    }
}

void DrinkMeter::reset() {
    currentLevel = 1.0f;
}

void DrinkMeter::draw() {
    DrawRectangleGradientV(
        GetScreenWidth() - 32, 
        GetScreenHeight()/2.0+128.0/2.0-128.0*currentLevel, 
        32, 
        128.0*currentLevel, 
        {0xda,0x62,0x0a,0xff}, 
        {0xfe, 0xcd, 0x3b, 0x90}
    );
}