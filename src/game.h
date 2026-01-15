#include "level.h"
#include <raylib.h>

#pragma once

class Game : public Level {
    private:
        Texture2D bg;
    public:
        void load() override;
        void unload() override;
        void loop() override;
};