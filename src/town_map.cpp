#include <cmath>
#include "town_map.h"

void TownMap::load() {
    map = LoadTexture("assets/mapa.png");

    currentPlayerTexture = LoadTexture("assets/student1_p.png");
    playerPosition = { (float)map.width / 2, (float)map.height / 2 };
    playerRotation = 0.0f;
    playerSpeed = 200.0f;

    camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    camera.target = playerPosition;
    camera.zoom = 1.0f;
}

void TownMap::unload() {
    UnloadTexture(map);
    UnloadTexture(currentPlayerTexture);
}

void TownMap::loop() {
    determinePlayerMovement(GetFrameTime());

    BeginDrawing();
    BeginMode2D(camera);

    DrawTexture(map, 0, 0, WHITE);
    DrawRectangle(400, map.height - 50, 50, 50, RED);
    DrawRectangle(10, map.height - 50, 50, 50, RED);

    /*if ((playerPosition.x > 400 && playerPosition.x < 450 &&
         playerPosition.y > map.height - 50 && playerPosition.y < map.height) || (playerPosition.x )) {
        LevelManager::changeLevel(new MainMenu());
    }*/

    // Zastosowane w celu mozliwosci ustawienia origin w srodku tekstury,
    // dzieki czemu obraca sie wzgledem srodka
    Rectangle source = { 0.0f, 0.0f, (float)currentPlayerTexture.width, (float)currentPlayerTexture.height };
    Rectangle dest = { playerPosition.x, playerPosition.y, (float)currentPlayerTexture.width, (float)currentPlayerTexture.height };
    Vector2 origin = { (float)currentPlayerTexture.width / 2, (float)currentPlayerTexture.height / 2 };

    DrawTexturePro(currentPlayerTexture, source, dest, origin, playerRotation, WHITE);

    EndMode2D();
    EndDrawing();
}

void TownMap::determinePlayerMovement(float deltaTime) {
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