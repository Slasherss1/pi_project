#include "game.h"
#include "masher.h"
#include "utils.h"
#include <raylib.h>
#include <string>

Masher mash = Masher();

void Game::load() {
    bg = LoadTexture("assets/concrete.png");
    mash.text = "Pij!";
}

void Game::unload() {
    UnloadTexture(bg);
}

void Game::loop() {
    mash.tick();

    BeginDrawing();
    DrawBackground(bg);
    mash.draw();

    EndDrawing();
}