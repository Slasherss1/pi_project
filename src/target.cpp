#include "target.h"
#include <raylib.h>

void Target::Draw() {
    DrawTexture(this->texture, this->position.x, this->position.y, WHITE);
}