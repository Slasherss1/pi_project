#include "target.h"
#include <raylib.h>

void Target::Draw() {
    DrawTexture(this->texture, this->position.x-32, this->position.y-32, WHITE);
}