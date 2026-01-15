#pragma once

#include <raylib.h>
#include <string>
#include <vector>
class Masher {
    private:
        bool pressed = false;
        int count = 0;
        std::string keyName;
    public:
        std::string text;

        std::vector<KeyboardKey> sequence = {KEY_SPACE};
        
        void tick();
        void draw();

        bool isPressed();
};