#include "drinkMeter.h"
#include "physObj.h"
#pragma once

class Projectile : public PhysicsObj {
    public:
        void Draw() override;
};

class AimableProjectile {
    private:
        bool isAiming = false;
        bool isShot = false;
        float force = 0.0;
    public:
        Texture2D texture;
        Vector2 position = {0.0f, 0.0f};

        Projectile** proj_pp = nullptr;

        DrinkMeter * drinkMeter = nullptr;

        void Draw();
        void Tick();
        void Shoot(Vector2);
};