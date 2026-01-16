#include "throwRound.h"
#include "drinkMeter.h"
#include "masher.h"
#include "utils.h"
#include <raylib.h>
#include <string>

Masher* drinkMash = new Masher();
DrinkMeter drinkMeter = DrinkMeter();

void ThrowRound::load() {
    bg = LoadTexture("assets/concrete.png");
    drinkMash->text = "Pij!";
    drinkMeter.sipSize = 0.1f;
}

void ThrowRound::unload() {
    UnloadTexture(bg);
    delete drinkMash;
    drinkMash = nullptr;
}

void ThrowRound::loop() {
    if (drinkMash) {
        drinkMash->tick();
        
        if (drinkMash->isPressed()) {
            drinkMeter.sip();
        }
    } 

    if (drinkMeter.currentLevel < 1e-9) {
        delete drinkMash;
        drinkMash = nullptr;
    }


    BeginDrawing();
    DrawBackground(bg);
    if (drinkMash) drinkMash->draw();
    drinkMeter.draw();

    EndDrawing();
}