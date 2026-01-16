#include "level.h"
#include <raylib.h>

#pragma once

class ThrowRound : public Level {
    private:
        Texture2D bg;
    public:
        void load() override;
        void unload() override;
        void loop() override;
};