#ifndef NDEBUG
#include <raylib.h>
#include "colliderHelpers.h"
#include "target.h"
#include "projectile.h"
#include "raymath.h"
#include "throwTest.h"

using namespace std;

void ThrowTest::load() {
    target.texture = LoadTexture("assets/cel.png");
    target.mass = 0.05; // gram
    target.coliderRadius = 23.0; // pixels
    target.crossSection = 0.01; // m^2
    target.safeZone.radius = 40.0;
    target.decay = 15.0;
    
    proj.position = {400.0, 400.0};
    proj.texture = LoadTexture("assets/zgniot.png");
    proj.proj_pp = &projectilePtr;
}

void ThrowTest::unload() {
    UnloadTexture(target.texture);
    UnloadTexture(proj.texture);
}

void ThrowTest::loop() {
    if (projectilePtr != nullptr) {
        projectilePtr->Tick();
        col.handleCollision(&target, projectilePtr);
    }
    proj.Tick();
    target.Tick();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    #ifndef NDEBUG
    DrawCircleV(target.safeZone.position, target.safeZone.radius, RED);
    DrawCircleV(target.position, target.coliderRadius, GOLD);
    if (projectilePtr != nullptr) {
        DrawCircleV(projectilePtr->position, projectilePtr->coliderRadius, BLUE);
        DrawLineEx(projectilePtr->position, Vector2Add(projectilePtr->position, projectilePtr->forceDir), 3, BLACK);
    }
    DrawLineEx(target.position, Vector2Add(target.position, target.forceDir), 3, BLACK);
    #endif

    target.Draw();
    proj.Draw();
    if (projectilePtr != nullptr) {
        projectilePtr->Draw();
    }

    EndDrawing();
}
#endif
