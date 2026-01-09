#include <raylib.h>
#pragma once

class PhysicsObj {
    public:
        Vector2 position = {0.0f, 0.0f};
        Vector2 velocity = {0.0f, 0.0f};
        float mass = 0.0;
        Vector2 forceDir = {0.0f, 0.0f};
        float crossSection = 0.0f;

        float coliderRadius = 0.0f;

        float decay = 0.0f;

        virtual ~PhysicsObj();
        Texture2D texture;
        void Tick();
        virtual void Draw();
};