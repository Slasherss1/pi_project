#include "game.h"
#include "drinkMeter.h"
#include "masher.h"
#include "utils.h"
#include <raylib.h>
#include <string>

Masher mash = Masher();
DrinkMeter drinkMeter = DrinkMeter();

void Game::load() {
    bg = LoadTexture("assets/concrete.png");
    mash.text = "Pij!";
    drinkMeter.sipSize = 0.1f;
}

void Game::unload() {
    UnloadTexture(bg);
}

void Game::loop() {
    mash.tick();

    if (mash.isPressed()) {
        drinkMeter.sip();
    }

    BeginDrawing();
    DrawBackground(bg);
    mash.draw();
    drinkMeter.draw();

    EndDrawing();
}