#include "game.h"
#include "utils.h"
#include <raylib.h>

void Game::load() {
    bg = LoadTexture("assets/concrete.png");
}

void Game::unload() {
    UnloadTexture(bg);
}

void Game::loop() {
    BeginDrawing();
    DrawBackground(bg);

    EndDrawing();
}