#pragma once
#include <raylib.h>
#include "level.h"

class TownMap : public Level {
public:
    void load() override;
    void unload() override;
    void loop() override;

private:
    Texture2D map;
    Texture2D currentPlayerTexture;
    Texture2D redMan;
    Rectangle playerBox;
    Vector2 playerPosition;
    float playerRotation;
    float playerSpeed;
    Camera2D camera;
    Rectangle shopEntry;
    Rectangle roundEntry;

    void determinePlayerMovement(float deltaTime);
    void updatePlayerHitBox();
};