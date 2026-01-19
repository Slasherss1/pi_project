#include <cmath>
#include <raylib.h>
#include "level.h"
#include "throwRound.h"
#include "utils.h"
#include "town_map.h"
#include "shop.h"
#include "menu.h"
#include "inventory.h"
#include "inventory_manager.h"

static const char* SHOP_NAME = "V STUDECIAK V";
static const char* INVENTORY_BUTTON = "Ekwipunek";

void TownMap::load() {
    map = LoadTexture("assets/mapa.png");
    redMan = LoadTexture("assets/miniczer1.png");

    currentPlayerTexture = LoadTexture("assets/miniziel1.png");
    playerPosition = { (float)map.width / 2, (float)map.height / 2 };
    playerRotation = 0.0f;
    playerSpeed = 200.0f;
	updatePlayerHitBox();

    camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    camera.target = playerPosition;
    camera.zoom = 1.0f;
    
    shopEntry = { 10, float(map.height - 50), 440, 50 };
    roundEntry = {1137, 420, 32, 32};
}

void TownMap::unload() {
    UnloadTexture(map);
    UnloadTexture(redMan);
    UnloadTexture(currentPlayerTexture);

	InventoryManager::getInstance().saveInventory(SAVE_FILE);
}

void TownMap::loop() {
    determinePlayerMovement(GetFrameTime());

	if (IsKeyDown(KEY_ESCAPE)) {
		LevelManager::changeLevel(new MainMenu());
		return;
	}

    BeginDrawing();
    BeginMode2D(camera);

    DrawTexture(map, 0, 0, WHITE);
    DrawText(SHOP_NAME, GetCenteredXInBounds(SHOP_NAME, 50, 60, 400), map.height - 50, 50, YELLOW);
    
	if (CheckCollisionRecs(playerBox, shopEntry)) {
        LevelManager::changeLevel(new Shop());
		return;
    }

    if (CheckCollisionRecs(playerBox, roundEntry)) {
        LevelManager::changeLevel(new ThrowRound());
        return;
    }

    // czerwony
    DrawTexturePro(redMan,
        { 0.0f, .0f, (float)redMan.width, (float)redMan.height },
        roundEntry,
        { 16.0f, 16.0f },
        0.0f,
        WHITE
    );

    
    // Zastosowane w celu mozliwosci ustawienia origin w srodku tekstury,
    // dzieki czemu obraca sie wzgledem srodka
    Rectangle source = { 0.0f, 0.0f, (float)currentPlayerTexture.width, (float)currentPlayerTexture.height };
    Rectangle dest = { playerPosition.x, playerPosition.y, (float)currentPlayerTexture.width, (float)currentPlayerTexture.height };
    Vector2 origin = { (float)currentPlayerTexture.width / 2, (float)currentPlayerTexture.height / 2 };
    
    DrawTexturePro(currentPlayerTexture, source, dest, origin, playerRotation, WHITE);
    
    EndMode2D();
	
	// Przycisk ekwipunku w prawym dolnym rogu
	int buttonFontSize = 30;
	int margin = 10;
	int buttonX = GetScreenWidth() - MeasureText(INVENTORY_BUTTON, buttonFontSize) - margin;
	int buttonY = GetScreenHeight() - buttonFontSize - margin;
	
	if (TextButton(INVENTORY_BUTTON, {(float)buttonX, (float)buttonY}, buttonFontSize, WHITE, YELLOW)) {
		LevelManager::changeLevel(new Inventory());
		return;
	}
	
    EndDrawing();
}

void TownMap::updatePlayerHitBox() {
    playerBox = {
        playerPosition.x - currentPlayerTexture.width / 2.0f,
        playerPosition.y - currentPlayerTexture.height / 2.0f,
        (float)currentPlayerTexture.width,
        (float)currentPlayerTexture.height
    };
}

void TownMap::determinePlayerMovement(float deltaTime) {
    Vector2 movement = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_W)) movement.y -= 1.0f;
    if (IsKeyDown(KEY_S)) movement.y += 1.0f;
    if (IsKeyDown(KEY_A)) movement.x -= 1.0f;
    if (IsKeyDown(KEY_D)) movement.x += 1.0f;

    if (movement.x != 0.0f || movement.y != 0.0f) {
		// eliminacja szybszego ruchu po przekatnej
        float length = sqrtf(movement.x * movement.x + movement.y * movement.y);
        movement.x /= length;
        movement.y /= length;

		// ustawienie rotacji gracza w kierunku ruchu
        playerRotation = atan2f(movement.y, movement.x) * RAD2DEG - 90.0f;

        playerPosition.x += movement.x * playerSpeed * deltaTime;
        playerPosition.y += movement.y * playerSpeed * deltaTime;
    }

	///// OBSLUGA KOLIZJI Z GRANICAMI MAPY /////
	updatePlayerHitBox();

    if (playerBox.x < 0) playerPosition.x = currentPlayerTexture.width / 2.0f;
    if (playerBox.y < 0) playerPosition.y = currentPlayerTexture.height / 2.0f;
    if (playerBox.x + playerBox.width > map.width)   playerPosition.x = map.width - currentPlayerTexture.width / 2.0f;
    if (playerBox.y + playerBox.height > map.height) playerPosition.y = map.height - currentPlayerTexture.height / 2.0f;

	updatePlayerHitBox();

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