#ifndef NDEBUG
#include <raylib.h>
#include "physObj.h"
#include "target.h"
#include "projectile.h"
#include "raymath.h"
#include "physicsTest.h"

using namespace std;

void PhysicsTest::load() {
    target.texture = LoadTexture("assets/cel.png");
    target.mass = 0.05; // gram
    target.colliderRadius = 23.0; // pixels
    target.crossSection = 0.01; // m^2
    target.safeZone.radius = 40.0;
    target.decay = 15.0;

    projectile.texture = LoadTexture("assets/zgniot.png");
    projectile.forceDir = {50.0, 35.0};
    projectile.mass = 0.05; // kg
    projectile.crossSection = 0.01; // m^2
    projectile.colliderRadius = 20.0; // pixels
    projectile.decay = 3.0;

}

void PhysicsTest::unload() {
    UnloadTexture(target.texture);
    UnloadTexture(projectile.texture);
}

void PhysicsTest::loop() {
    projectile.Tick();
    col.handleCollision(&target, &projectile);
    target.Tick();
    
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    #ifndef NDEBUG
    DrawCircleV(target.safeZone.position, target.safeZone.radius, RED);
    DrawCircleV(target.position, target.colliderRadius, GOLD);
    DrawCircleV(projectile.position, projectile.colliderRadius, BLUE);
    DrawLineEx(projectile.position, Vector2Add(projectile.position, projectile.forceDir), 3, BLACK);
    DrawLineEx(target.position, Vector2Add(target.position, target.forceDir), 3, BLACK);
    #endif
    
    target.Draw();
    projectile.Draw();
    
    EndDrawing();
}
#endif