#include "projectile.h"
#include <raylib.h>

void Projectile::Draw() {
    DrawTexture(this->texture, this->position.x-32, this->position.y-32, WHITE);
}