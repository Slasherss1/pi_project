#include "game.h"
#include "utils.h"

static const char* GAME_NAME = "Flanki";
static const char* NEW_GAME = "Nowa gra";
static const char* LOAD_GAME = "Wczytaj gre";
static const char* SETTINGS = "Ustawienia";
static const char* SELECT_DIFFICULTY = "Wybierz poziom trudnosci";
static const char* EXPERIENCED = "Doswiadczony student";
static const char* EASY = "Poziom trudnosci: latwy";
static const char* FRESHMAN = "Swiezak";
static const char* HARD = "Poziom trudnosci: trudny";
static const char* GO_BACK = "Wroc";

Game::Game() : state(GameState::START), difficulty(GameDifficulty::EASY) {
    menuTexture = LoadTexture("assets/menu.png");
    settingsTexture = LoadTexture("assets/settings.png");
    freshman = LoadTexture("assets/swiezak.png");
    experienced = LoadTexture("assets/doswiadczony.png");
}

Game::~Game() {
    UnloadTexture(menuTexture);
    UnloadTexture(settingsTexture);
    UnloadTexture(freshman);
    UnloadTexture(experienced);
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

    DrawText(GAME_NAME, GetCenteredX(GAME_NAME, 100), 120, 100, YELLOW);

    if (TextButton(NEW_GAME, {GetCenteredX(NEW_GAME, 40), 250}, 40, WHITE, RED)) state = GameState::GAME;
    if (TextButton(LOAD_GAME, {GetCenteredX(LOAD_GAME, 40), 320}, 40, WHITE, RED)) state = GameState::GAME;
    if (TextButton(SETTINGS, {GetCenteredX(SETTINGS, 40), 390}, 40, WHITE, RED)) state = GameState::SETTINGS;
}

void Game::DrawSettingsMenu() {
    DrawBackground(settingsTexture);

    DrawText(SELECT_DIFFICULTY, GetCenteredX(SELECT_DIFFICULTY, 45), 20, 45, YELLOW);

    bool isEasyMode = (difficulty == GameDifficulty::EASY);
    Color easyColor = isEasyMode ? RED : WHITE;
    Color hardColor = isEasyMode ? WHITE : RED;

    if (TextureButton(experienced, {35, 110}, WHITE)
        || TextButton(EXPERIENCED, {GetCenteredXInBounds(EXPERIENCED, 20, 0, 400), 450}, 20, easyColor, easyColor)
        || TextButton(EASY, {GetCenteredXInBounds(EASY, 20, 0, 400), 480}, 20, easyColor, easyColor))
        difficulty = GameDifficulty::EASY;

    if (TextureButton(freshman, {430, 110}, WHITE)
        || TextButton(FRESHMAN, {GetCenteredXInBounds(FRESHMAN, 20, 400, 800), 450}, 20, hardColor, hardColor)
        || TextButton(HARD, {GetCenteredXInBounds(HARD, 20, 400, 800), 480}, 20, hardColor, hardColor))
        difficulty = GameDifficulty::HARD;

    if (IsKeyPressed(KEY_SPACE)) state = GameState::START;
}

void Game::DrawGame() {
    ClearBackground(RAYWHITE);
}