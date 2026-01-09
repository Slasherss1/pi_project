#include <raylib.h>
#include "target.h"
#include "projectile.h"
#include "raymath.h"

using namespace std;
int main() {
    InitWindow(800, 600, "Flanki");
    
    Target target({400.0, 300.0});
    target.texture = LoadTexture("assets/cel.png");
    target.mass = 0.05; // gram
    target.coliderRadius = 23.0; // pixels
    target.crossSection = 0.01; // m^2
    target.safeZone.radius = 50.0;
    target.decay = 15.0;

    Projectile projectile;
    projectile.texture = LoadTexture("assets/zgniot.png");
    projectile.forceDir = {50.0, 37.0};
    projectile.mass = 0.05; // kg
    projectile.crossSection = 0.01; // m^2
    projectile.coliderRadius = 20.0; // pixels
    projectile.decay = 5.0;

    #ifndef NDEBUG
    SetTraceLogLevel(LOG_DEBUG);
    #endif

    while (!WindowShouldClose()) {
        projectile.Tick();
        if (CheckCollisionCircles(target.position, target.coliderRadius, projectile.position, projectile.coliderRadius)) {
            target.velocity = projectile.velocity;
            projectile.velocity = Vector2Zero();
            target.forceDir = projectile.forceDir;
            projectile.forceDir = Vector2Zero();

            #ifndef NDEBUG
            DrawText("Collision Detected!", 300, 50, 20, RED);
            #endif
        }

        target.Tick();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        #ifndef NDEBUG
        DrawCircleV(target.safeZone.position, target.safeZone.radius, RED);
        DrawCircleV(target.position, target.coliderRadius, GOLD);
        DrawCircleV(projectile.position, projectile.coliderRadius, BLUE);
        #endif

        target.Draw();
        projectile.Draw();

        EndDrawing();
    }

    UnloadTexture(target.texture);
    UnloadTexture(projectile.texture);

    CloseWindow();
    return 0;
}