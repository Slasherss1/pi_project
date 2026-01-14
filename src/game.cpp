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
    whiteMan = LoadTexture("assets/whiteMan.png");
    redMan = LoadTexture("assets/redman.png");
}

Game::~Game() {
    UnloadTexture(menuTexture);
    UnloadTexture(settingsTexture);
    UnloadTexture(whiteMan);
    UnloadTexture(redMan);
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
    Texture2D easyTexture = isEasyMode ? redMan : whiteMan;;
    Texture2D hardTexture = isEasyMode ? whiteMan : redMan;;

    if (TextureButton(easyTexture, {100, 90}, WHITE)
        or TextButton(EXPERIENCED, {GetCenteredXInBounds(EXPERIENCED, 20, 0, 400), 500}, 20, easyColor, easyColor)
        or TextButton(EASY, {GetCenteredXInBounds(EASY, 20, 0, 400), 530}, 20, easyColor, easyColor))
        difficulty = GameDifficulty::EASY;

    if (TextureButton(hardTexture, {500, 90}, WHITE)
        or TextButton(FRESHMAN, {GetCenteredXInBounds(FRESHMAN, 20, 400, 800), 500}, 20, hardColor, hardColor)
        or TextButton(HARD, {GetCenteredXInBounds(HARD, 20, 400, 800), 530}, 20, hardColor, hardColor))
        difficulty = GameDifficulty::HARD;

    if (IsKeyPressed(KEY_SPACE)) state = GameState::START;
}

void Game::DrawGame() {
    ClearBackground(RAYWHITE);
}