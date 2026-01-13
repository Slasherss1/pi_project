#include "game.h"
#include "utils.h"

Game::Game() : state(GameState::START), difficulty(GameDifficulty::EASY) {
    menuTexture = LoadTexture("assets/menu.png");
    settingsTexture = LoadTexture("assets/settings.png");
}

Game::~Game() {
    UnloadTexture(menuTexture);
    UnloadTexture(settingsTexture);
}

void Game::Run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        switch (state) {
            case GameState::START:
                DrawStartMenu();
                break;
            case GameState::SETTINGS:
                DrawSettingsMenu();
                break;
            case GameState::GAME:
                DrawGame();
                break;
        }
        EndDrawing();
    }
    CloseWindow();
}

void Game::DrawStartMenu() {
    DrawBackground(menuTexture);
    DrawText("Flanki", GetCenteredX("Flanki", 100), 120, 100, YELLOW);
    if (TextButton("Nowa gra", {GetCenteredX("Nowa gra", 40), 250}, 40, WHITE, RED)) state = GameState::GAME;
    if (TextButton("Wczytaj gre", {GetCenteredX("Wczytaj gre", 40), 320}, 40, WHITE, RED)) state = GameState::GAME;
    if (TextButton("Ustawienia", {GetCenteredX("Ustawienia", 40), 390}, 40, WHITE, RED)) state = GameState::SETTINGS;
}

void Game::DrawSettingsMenu() {
    DrawBackground(settingsTexture);
}

void Game::DrawGame() {
    ClearBackground(RAYWHITE);
}