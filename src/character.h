#pragma once
#include <raylib.h>

class Character {
    private:
        Vector2 position;
        float initAngle;
        
        public:
        Character(Vector2 initPos, float initAngle);
        Vector2 targetPos;
        Vector2 initPos;

        float stepDist = 10.0f;
        void step();

        Texture2D texture;

        void Tick();
        void Draw();

        bool hasReachedTarget();
};