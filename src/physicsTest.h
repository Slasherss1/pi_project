#pragma once
#ifndef NDEBUG
#include "colliderHelpers.h"
#include "level.h"
#include "target.h"
#include "projectile.h"
class PhysicsTest : public Level {
    public:
        void load() override;
        void unload() override;
        void loop() override;

    private:
        Target target{{400.0, 300.0}};
        Projectile projectile{};
        CollideAndBounce col;

};

#endif