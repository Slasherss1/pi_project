#pragma once
#include "colliderHelpers.h"
#include "projectile.h"
#include "target.h"
#include "level.h"
#ifndef NDEBUG

class ThrowTest : public Level {
    private:
        Target target{{400.0, 150.0}};
        Projectile* projectilePtr = nullptr;
        AimableProjectile proj;
        CollideAndBounce col;
    public:
        void load() override;
        void unload() override;
        void loop() override;
};

#endif