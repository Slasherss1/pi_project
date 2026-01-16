#include "menu.h"
#include "level.h"
#include "utils.h"
#include "town_map.h"

static const char* GAME_NAME = "Flanki";
static const char* NEW_GAME = "Nowa gra";
static const char* LOAD_GAME = "Wczytaj gre";
static const char* SETTINGS = "Ustawienia";
static const char* SELECT_DIFFICULTY = "Wybierz poziom trudnosci";
static const char* EXPERIENCED = "Weteran";
static const char* EASY = "Poziom trudnosci: latwy";
static const char* FRESHMAN = "Swiezak";
static const char* HARD = "Poziom trudnosci: trudny";
static const char* GO_BACK = "Wroc";

#pragma region Menu
void MainMenu::load() {
    menuTexture = LoadTexture("assets/menu.png");
}

void MainMenu::unload() {
    UnloadTexture(menuTexture);
}

void MainMenu::loop() {
    BeginDrawing();
    DrawBackground(menuTexture);

    DrawText(GAME_NAME, GetCenteredX(GAME_NAME, 100), 120, 100, YELLOW);

    if (TextButton(NEW_GAME, {GetCenteredX(NEW_GAME, 40), 250}, 40, WHITE, RED)) LevelManager::changeLevel(new TownMap());
    if (TextButton(LOAD_GAME, {GetCenteredX(LOAD_GAME, 40), 320}, 40, WHITE, RED)) LevelManager::changeLevel(new TownMap());
    if (TextButton(SETTINGS, {GetCenteredX(SETTINGS, 40), 390}, 40, WHITE, RED)) LevelManager::changeLevel(new SettingsMenu());
    EndDrawing();
}
#pragma endregion

#pragma region Settings
void SettingsMenu::load() {
    settingsTexture = LoadTexture("assets/settings.png");
    freshman = LoadTexture("assets/swiezak.png");
    veteran = LoadTexture("assets/weteran.png");
}

void SettingsMenu::unload() {
    UnloadTexture(settingsTexture);
    UnloadTexture(freshman);
    UnloadTexture(veteran);
}

void SettingsMenu::loop() {
    bool isEasyMode = (difficulty == GameDifficulty::EASY);
    Color easyColor = isEasyMode ? RED : WHITE;
    Color hardColor = isEasyMode ? WHITE : RED;
    if (IsKeyPressed(KEY_SPACE)) LevelManager::changeLevel(new MainMenu());
    
    BeginDrawing();
    DrawBackground(settingsTexture);

    DrawText(SELECT_DIFFICULTY, GetCenteredX(SELECT_DIFFICULTY, 45), 20, 45, YELLOW);

    if (TextureButton(veteran, {30, 110}, WHITE)
        || TextButton(EXPERIENCED, {GetCenteredXInBounds(EXPERIENCED, 20, 0, 400), 450}, 20, easyColor, easyColor)
        || TextButton(EASY, {GetCenteredXInBounds(EASY, 20, 0, 400), 480}, 20, easyColor, easyColor))
        difficulty = GameDifficulty::EASY;

    if (TextureButton(freshman, {430, 110}, WHITE)
        || TextButton(FRESHMAN, {GetCenteredXInBounds(FRESHMAN, 20, 400, 800), 450}, 20, hardColor, hardColor)
        || TextButton(HARD, {GetCenteredXInBounds(HARD, 20, 400, 800), 480}, 20, hardColor, hardColor))
        difficulty = GameDifficulty::HARD;
    
    EndDrawing();
}
#pragma endregion