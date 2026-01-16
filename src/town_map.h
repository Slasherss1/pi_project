#pragma once
#include <raylib.h>
#include <array>
#include "level.h"

class TownMap : public Level {
public:
    void load() override;
    void unload() override;
    void loop() override;

private:
    Texture2D map;
    Texture2D currentPlayerTexture;
    Rectangle playerBox;
    Vector2 playerPosition;
    float playerRotation;
    float playerSpeed;
    Camera2D camera;
    std::array<Rectangle, 2> shopLocations;

    void determinePlayerMovement(float deltaTime);
    void updatePlayerHitBox();
};