#include "game.h"
#include "drinkMeter.h"
#include "masher.h"
#include "utils.h"
#include <raylib.h>
#include <string>

Masher drinkMash = Masher();
DrinkMeter drinkMeter = DrinkMeter();

void Game::load() {
    bg = LoadTexture("assets/concrete.png");
    drinkMash.text = "Pij!";
    drinkMeter.sipSize = 0.1f;
}

void Game::unload() {
    UnloadTexture(bg);
}

void Game::loop() {
    drinkMash.tick();

    if (drinkMash.isPressed()) {
        drinkMeter.sip();
    }

    BeginDrawing();
    DrawBackground(bg);
    drinkMash.draw();
    drinkMeter.draw();

    EndDrawing();
}