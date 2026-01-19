#include "character.h"
#include "colliderHelpers.h"
#include "drinkMeter.h"
#include "level.h"
#include "masher.h"
#include "projectile.h"
#include "target.h"
#include <raylib.h>

#pragma once

class ThrowRound : public Level {
    private:
        Texture2D bg;
        Target target{{400.0, 300.0}};
        AimableProjectile ap;
        Projectile* proj = nullptr;
        CollideAndBounce col;
        Character character{{400.0, 550.0}, 180.0f};
        Masher * drinkMash = nullptr;
        DrinkMeter drinkMeter;
        Texture2D redMan;
    public:
        void load() override;
        void unload() override;
        void loop() override;
};