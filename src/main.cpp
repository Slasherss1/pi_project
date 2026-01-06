#include <iostream>
#include <raylib.h>
#include "target.h"
#include "projectile.h"

using namespace std;
int main() {
    cout << "Hello, World!" << endl;
    InitWindow(800, 600, "Hello Raylib");
    
    Target target;
    target.texture = LoadTexture("assets/cel.png");
    target.position = {400.0, 300.0};
    target.mass = 0.05; // gram

    Projectile projectile;
    projectile.texture = LoadTexture("assets/zgniot.png");
    projectile.forceDir = {1.0, 0.0};
    projectile.force = 100.0; // Newton
    projectile.mass = 0.05; // kg
    projectile.crossSection = 0.01; // m^2

    SetTraceLogLevel(LOG_DEBUG);

    while (!WindowShouldClose()) {
        target.Tick();
        projectile.Tick();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Raylib!", 190, 200,20, LIGHTGRAY);

        target.Draw();
        projectile.Draw();

        EndDrawing();
    }

    UnloadTexture(target.texture);
    UnloadTexture(projectile.texture);

    CloseWindow();
    return 0;
}