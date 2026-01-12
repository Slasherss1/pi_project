#include "target.h"
#include <raylib.h>
#include <raymath.h>

Target::Target(Vector2 pos) {
    this->safeZone.position = pos;
    this->position = pos;
}

void Target::Draw() {
    if (CheckCollisionPointCircle(this->position, this->safeZone.position, this->safeZone.radius)) {
        DrawTexture(this->texture, this->position.x-32, this->position.y-32, WHITE);
    } else {
        DrawTextureEx(this->texture, this->position, 90, 1, WHITE);
    }
}