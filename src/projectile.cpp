#include "projectile.h"
#include "beer_effect.h"
#include "beer_registry.h"
#include "inventory_manager.h"
#include "utils.h"
#include <algorithm>
#include <cmath>
#include <raylib.h>
#include <raymath.h>

void Projectile::Draw() {
    DrawTexture(this->texture, this->position.x-32, this->position.y-32, WHITE);
}

#define POWER 2
#define map_exp(from, to, power, value) (to * (pow(value/from, power)))

#define XP_FORCE_MULTIPLIER 0.5  // TODO: Zmieniać na podstawie poziomu trudności (#8)

float ForceMeterTick() {
    static float force = 0.0;
    static bool increasing = true;
    float effect_multiplier = 1.0;
    const BeerEffect* forceEffect = beerByNameHasEffect(InventoryManager::getInstance().getChosenBeer(), SLOWER_SPEED_ADJUSTMENT);
    if (forceEffect) {
        effect_multiplier = forceEffect->value;
    }
    if (increasing) {
        force += GetFrameTime() * pow(10, POWER) * XP_FORCE_MULTIPLIER * effect_multiplier; // TODO: Zamienić XP_FORCE_MULTIPLIER na zmienną z poziomu trudności (#8)
        if (force >= 128.0) {
            force = 128.0;
            increasing = false;
        }
    } else {
        force -= GetFrameTime() * pow(10, POWER) * XP_FORCE_MULTIPLIER * effect_multiplier; // TODO: Zamienić XP_FORCE_MULTIPLIER na zmienną z poziomu trudności (#8)
        if (force <= 0.0) {
            force = 0.0;
            increasing = true;
        }
    }
    return force;
}

void AimableProjectile::Draw() {
    if (isShot) return;
    if (isAiming) {
        const float angle = Vector2Angle(Vector2Subtract(GetMousePosition(), this->position), {-1.0, 0.0});
        #ifdef NDEBUG
        const BeerEffect* crosshairEffect = beerByNameHasEffect(InventoryManager::getInstance().getChosenBeer(), CROSSHAIR);
        if (
            crosshairEffect
        ) {
        #endif
        DrawLineV(this->position, Vector2Add(Vector2Rotate({10000,0}, -angle), this->position), BLACK);
        #ifdef NDEBUG
        }
        #endif
        DrawRing(this->position, 32, 64, -angle*RAD2DEG+5, -angle*RAD2DEG-5, 5, BLACK);
        DrawRectangleGradientV(GetRenderWidth() - 48, GetRenderHeight() - force, 48, force, RED, GREEN);
    }
    DrawTexture(this->texture, this->position.x-32, this->position.y-32, WHITE);
}

void AimableProjectile::Tick() {
    if (isShot) return;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        isAiming = true;
        force = ForceMeterTick();
    } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        isAiming = false;
        this->Shoot(Vector2Subtract(GetMousePosition(), this->position));
    }
}

void AimableProjectile::Shoot(Vector2 forceDir) {
    isShot = true;
    *proj_pp = new Projectile();
    (*proj_pp)->position = this->position;
    (*proj_pp)->texture = this->texture;
    (*proj_pp)->forceDir = Vector2Negate(Vector2Scale(Vector2Normalize(forceDir), map_exp(128, 250, 3, force)));
    (*proj_pp)->mass = 0.05; // kg
    (*proj_pp)->crossSection = 0.01; // m^2
    (*proj_pp)->colliderRadius = 20.0; // pixels
    (*proj_pp)->decay = 3.0;
}