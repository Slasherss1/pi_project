#include <iostream>
#include <raylib.h>
#include "target.h"
#include "projectile.h"
#include "raymath.h"

using namespace std;
int main() {
    cout << "Hello, World!" << endl;
    InitWindow(800, 600, "Hello Raylib");
    
    Target target({400.0, 300.0});
    target.texture = LoadTexture("assets/cel.png");
    target.mass = 0.05; // gram
    target.coliderRadius = 23.0f; // pixels
    target.crossSection = 0.01; // m^2
    target.safeZone.radius = 50.0f;

    Projectile projectile;
    projectile.texture = LoadTexture("assets/zgniot.png");
    projectile.forceDir = {50.0, 35.0};
    projectile.mass = 0.05; // kg
    projectile.crossSection = 0.01; // m^2
    projectile.coliderRadius = 20.0f; // pixels

    SetTraceLogLevel(LOG_DEBUG);

    while (!WindowShouldClose()) {
        projectile.Tick();
        if (CheckCollisionCircles(target.position, target.coliderRadius, projectile.position, projectile.coliderRadius)) {
            target.velocity = projectile.velocity;
            projectile.velocity = Vector2Zero();
            target.forceDir = projectile.forceDir;
            projectile.forceDir = Vector2Zero();

            DrawText("Collision Detected!", 300, 50, 20, RED);
        }

        const float forceDecayPerSecond = 15.0f;
        float fLen = Vector2Length(target.forceDir);
        if (fLen > 0.0f) {
            float newLen = fLen - forceDecayPerSecond * GetFrameTime();
            if (newLen <= 0.0f) target.forceDir = Vector2Zero();
            else target.forceDir = Vector2Scale(Vector2Normalize(target.forceDir), newLen);
        }
        target.Tick();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Raylib!", 190, 200,20, LIGHTGRAY);

        DrawCircleV(target.safeZone.position, target.safeZone.radius, RED);
        DrawCircleV(target.position, target.coliderRadius, GOLD);
        DrawCircleV(projectile.position, projectile.coliderRadius, BLUE);

        target.Draw();
        projectile.Draw();


        EndDrawing();
    }

    UnloadTexture(target.texture);
    UnloadTexture(projectile.texture);

    CloseWindow();
    return 0;
}