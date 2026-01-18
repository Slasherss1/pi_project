#include "menu.h"
#include "level.h"
#include "physicsTest.h"
#include "throwTest.h"
#include "utils.h"
#include "town_map.h"
#include "inventory_manager.h"

static const char* GAME_NAME = "Flanki";
static const char* NEW_GAME = "Nowa gra";
static const char* LOAD_GAME = "Wczytaj gre";
static const char* SETTINGS = "Ustawienia";
static const char* SELECT_DIFFICULTY = "Wybierz poziom trudnosci";
static const char* EXPERIENCED = "Weteran";
static const char* EASY_INFO = "Poziom trudnosci: latwy";
static const char* FRESHMAN = "Swiezak";
static const char* HARD_INFO = "Poziom trudnosci: trudny";
static const char* GO_BACK = "Wroc";
static const char* OVERWRITE_TITLE = "Wykryto zapisany stan gry";
static const char* OVERWRITE_MESSAGE = "Czy chcesz nadpisac zapisana gre?";
static const char* YES = "Tak";
static const char* NO = "Nie";

#pragma region Menu
void MainMenu::load() {
    menuTexture = LoadTexture("assets/menu.png");
    showOverwriteDialog = false;
}

void MainMenu::unload() {
    UnloadTexture(menuTexture);
}

void MainMenu::loop() {
    InventoryManager& inventory = InventoryManager::getInstance();
    
    BeginDrawing();
    DrawBackground(menuTexture);

    DrawText(GAME_NAME, GetCenteredX(GAME_NAME, 100), 120, 100, YELLOW);

    if (!showOverwriteDialog) {
        if (TextButton(NEW_GAME, {GetCenteredX(NEW_GAME, 40), 250}, 40, WHITE, RED)) {
            if (FileExists(SAVE_FILE)) {
                showOverwriteDialog = true;
            } else {
                inventory.resetInventory();
                LevelManager::changeLevel(new TownMap());
            }
        }
        
        if (TextButton(LOAD_GAME, {GetCenteredX(LOAD_GAME, 40), 320}, 40, WHITE, RED)) {
            if (inventory.loadInventory(SAVE_FILE)) {
                LevelManager::changeLevel(new TownMap());
            } else {
                inventory.resetInventory();
                LevelManager::changeLevel(new TownMap());
            }
        }
        
        if (TextButton(SETTINGS, {GetCenteredX(SETTINGS, 40), 390}, 40, WHITE, RED)) {
            LevelManager::changeLevel(new SettingsMenu());
        }
        #ifndef NDEBUG
        if (TextButton("DEBUG", {0,GetScreenHeight()-42.0f}, 42, BLUE, RED)) LevelManager::changeLevel(new DebugChooserMenu());
        #endif
    }
    
    if (showOverwriteDialog) {
        DrawOverwriteDialog();
    }
    
    EndDrawing();
}

void MainMenu::DrawOverwriteDialog() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.7f));

    int dialogWidth = 500;
    int dialogHeight = 250;
    int dialogX = (GetScreenWidth() - dialogWidth) / 2;
    int dialogY = (GetScreenHeight() - dialogHeight) / 2;

    DrawRectangle(dialogX, dialogY, dialogWidth, dialogHeight, DARKGRAY);
    DrawRectangleLines(dialogX, dialogY, dialogWidth, dialogHeight, YELLOW);

    DrawText(OVERWRITE_TITLE, GetCenteredX(OVERWRITE_TITLE, 30), dialogY + 30, 30, YELLOW);
    DrawText(OVERWRITE_MESSAGE, GetCenteredX(OVERWRITE_MESSAGE, 20), dialogY + 80, 20, WHITE);

    int buttonY = dialogY + 150;
    if (TextButton(YES, { GetCenteredXInBounds(YES, 30, dialogX, dialogX + dialogWidth / 2), (float)buttonY }, 30, WHITE, RED)) {
        InventoryManager::getInstance().resetInventory();
        showOverwriteDialog = false;
        LevelManager::changeLevel(new TownMap());
    }

    if (TextButton(NO, { GetCenteredXInBounds(NO, 30, dialogX + dialogWidth / 2, dialogX + dialogWidth), (float)buttonY }, 30, WHITE, RED)) {
        showOverwriteDialog = false;
    }
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
	InventoryManager& inventory = InventoryManager::getInstance();

    bool isEasyMode = (inventory.getDifficulty() == GameDifficulty::EASY);
    Color easyColor = isEasyMode ? RED : WHITE;
    Color hardColor = isEasyMode ? WHITE : RED;
    if (IsKeyPressed(KEY_SPACE)) LevelManager::changeLevel(new MainMenu());
    
    BeginDrawing();
    DrawBackground(settingsTexture);

    DrawText(SELECT_DIFFICULTY, GetCenteredX(SELECT_DIFFICULTY, 45), 20, 45, YELLOW);

    if (TextureButton(veteran, {35, 110}, WHITE)
        || TextButton(EXPERIENCED, {GetCenteredXInBounds(EXPERIENCED, 20, 0, 400), 450}, 20, easyColor, easyColor)
        || TextButton(EASY_INFO, {GetCenteredXInBounds(EASY_INFO, 20, 0, 400), 480}, 20, easyColor, easyColor))
        inventory.setDifficulty(GameDifficulty::EASY);

    if (TextureButton(freshman, {430, 110}, WHITE)
        || TextButton(FRESHMAN, {GetCenteredXInBounds(FRESHMAN, 20, 400, 800), 450}, 20, hardColor, hardColor)
        || TextButton(HARD_INFO, {GetCenteredXInBounds(HARD_INFO, 20, 400, 800), 480}, 20, hardColor, hardColor))
        inventory.setDifficulty(GameDifficulty::HARD);
    
    EndDrawing();
}
#pragma endregion

#pragma region DebugChooser
#ifndef NDEBUG
void DebugChooserMenu::load() {
    // Load resources if needed
}
void DebugChooserMenu::unload() {
    // Unload resources if needed
}
void DebugChooserMenu::loop() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (TextButton("Physics", {0,0}, 22, BLACK, RED)) LevelManager::changeLevel(new PhysicsTest());
    if (TextButton("Throw", {0,22}, 22, BLACK, RED)) LevelManager::changeLevel(new ThrowTest());

    EndDrawing();
}
#endif
#pragma endregion