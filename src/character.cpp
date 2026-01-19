#include "character.h"
#include <raylib.h>
#include <raymath.h>

Character::Character(Vector2 initPos, float initAngle) {
    this->position = initPos;
    this->initPos = initPos;
    this->initAngle = initAngle;
}

void Character::Tick() {
    // Update character logic here
}

void Character::step() {
    position = Vector2MoveTowards(position, targetPos, stepDist);
}

void Character::Draw() {
    float angle;
    if (Vector2Distance(this->position, this->initPos) < 1.0f) {
        angle = initAngle;
    } else {
        angle = atan2f(targetPos.y - position.y, targetPos.x - position.x) * (180.0f / PI) - 90.0f;
    }
    DrawTexturePro(texture, {0, 0, 128, 128}, {position.x, position.y, 128, 128}, {64,64}, angle, WHITE);
}

bool Character::hasReachedTarget() {
    return Vector2Distance(this->position, this->targetPos) < 1.0f;
}