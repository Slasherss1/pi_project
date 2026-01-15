#include <raylib.h>
#include <cmath>
#include "game.h"
#include "level.h"
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

    if (TextButton(NEW_GAME, {GetCenteredX(NEW_GAME, 40), 250}, 40, WHITE, RED)) LevelManager::changeLevel(new Game());
    if (TextButton(LOAD_GAME, {GetCenteredX(LOAD_GAME, 40), 320}, 40, WHITE, RED)) LevelManager::changeLevel(new Game());
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

#pragma region Game
void Game::load() {
    map = LoadTexture("assets/mapa.png");

    currentPlayerTexture = LoadTexture("assets/student1_p.png");
    playerPosition = { (float)map.width / 2, (float)map.height / 2 };
    playerRotation = 0.0f;
    playerSpeed = 200.0f;

    camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    camera.target = playerPosition;
    camera.zoom = 1.0f;
}

void Game::unload() {
    UnloadTexture(map);
    UnloadTexture(currentPlayerTexture);
}

void Game::loop() {
    determinePlayerMovement(GetFrameTime());

    BeginDrawing();
	BeginMode2D(camera);

    DrawTexture(map, 0, 0, WHITE);

	// Zastosowane w celu mozliwosci ustawienia origin w srodku tekstury,
	// dzieki czemu obraca sie wzgledem srodka
    Rectangle source = { 0.0f, 0.0f, (float)currentPlayerTexture.width, (float)currentPlayerTexture.height };
    Rectangle dest = { playerPosition.x, playerPosition.y, (float)currentPlayerTexture.width, (float)currentPlayerTexture.height };
    Vector2 origin = { (float)currentPlayerTexture.width / 2, (float)currentPlayerTexture.height / 2 };

    DrawTexturePro(currentPlayerTexture, source, dest, origin, playerRotation, WHITE);

	EndMode2D();
	EndDrawing();
}

void Game::determinePlayerMovement(float deltaTime) {
    Vector2 movement = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_W)) movement.y -= 1.0f;
    if (IsKeyDown(KEY_S)) movement.y += 1.0f;
    if (IsKeyDown(KEY_A)) movement.x -= 1.0f;
    if (IsKeyDown(KEY_D)) movement.x += 1.0f;

    if (movement.x != 0.0f || movement.y != 0.0f) {
        // To usuwa problem szybszego poruszania sie po przekatnej
        float length = sqrtf(movement.x * movement.x + movement.y * movement.y);
        movement.x /= length;
        movement.y /= length;

        // To ustawia rotacje gracza w kierunku ruchu
        playerRotation = atan2f(movement.y, movement.x) * RAD2DEG - 90.0f;

        playerPosition.x += movement.x * playerSpeed * deltaTime;
        playerPosition.y += movement.y * playerSpeed * deltaTime;
    }

    float halfWidth = (float)currentPlayerTexture.width / 2.0f;
    float halfHeight = (float)currentPlayerTexture.height / 2.0f;

    if (playerPosition.x - halfWidth < 0) playerPosition.x = halfWidth;
    if (playerPosition.y - halfHeight < 0) playerPosition.y = halfHeight;
    if (playerPosition.x + halfWidth > map.width) playerPosition.x = map.width - halfWidth;
    if (playerPosition.y + halfHeight > map.height) playerPosition.y = map.height - halfHeight;

    camera.target = playerPosition;

    float screenWidth = (float)GetScreenWidth() / camera.zoom;
    float screenHeight = (float)GetScreenHeight() / camera.zoom;

    float minX = screenWidth / 2.0f;
    float minY = screenHeight / 2.0f;
    float maxX = map.width - screenWidth / 2.0f;
    float maxY = map.height - screenHeight / 2.0f;

    if (map.width > screenWidth) {
        if (camera.target.x < minX) camera.target.x = minX;
        if (camera.target.x > maxX) camera.target.x = maxX;
    }
    else {
        camera.target.x = (float)map.width / 2.0f;
    }

    if (map.height > screenHeight) {
        if (camera.target.y < minY) camera.target.y = minY;
        if (camera.target.y > maxY) camera.target.y = maxY;
    }
    else {
        camera.target.y = (float)map.height / 2.0f;
    }
}

#pragma endregion