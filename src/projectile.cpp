#include "projectile.h"
#include <raylib.h>

void Projectile::Draw() {
    DrawTexture(this->texture, this->position.x, this->position.y, WHITE);
}