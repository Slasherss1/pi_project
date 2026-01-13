#include <raylib.h>
#include "physObj.h"
#include "target.h"
#include "projectile.h"
#include "raymath.h"

using namespace std;

void ColisionHandler(bool coliding, PhysicsObj& target, PhysicsObj& projectile) {
    static bool isColliding = false;
    if (coliding) {
        if (isColliding) return;
        isColliding = true;
    } else {
        isColliding = false;
        return;
    }
    const Vector2 angleDir = Vector2Negate(Vector2Subtract(projectile.position, target.position));
    const Vector2 impact = Vector2Add(projectile.forceDir, target.forceDir);
    const Vector2 totalVelocity = Vector2Add(projectile.velocity, target.velocity);
    const float totalMass = projectile.mass + target.mass;
    const float angle = Vector2Angle(angleDir, projectile.forceDir);
    const float nangle = angle - PI;
    target.velocity = Vector2Rotate(Vector2Scale(totalVelocity, projectile.mass / totalMass), angle);
    projectile.velocity = Vector2Rotate(Vector2Scale(totalVelocity, target.mass / totalMass), nangle);
    target.forceDir = Vector2Rotate(Vector2Scale(impact, projectile.mass / totalMass), angle);
    projectile.forceDir = Vector2Rotate(Vector2Scale(impact, target.mass / totalMass), nangle);

    #ifndef NDEBUG
    DrawText("Collision Detected!", 300, 50, 20, RED);
    #endif
}

int main() {
    InitWindow(800, 600, "Flanki");
    
    Target target({400.0, 300.0});
    target.texture = LoadTexture("assets/cel.png");
    target.mass = 0.05; // gram
    target.coliderRadius = 23.0; // pixels
    target.crossSection = 0.01; // m^2
    target.safeZone.radius = 40.0;
    target.decay = 15.0;

    Projectile projectile;
    projectile.texture = LoadTexture("assets/zgniot.png");
    projectile.forceDir = {50.0, 35.0};
    projectile.mass = 0.05; // kg
    projectile.crossSection = 0.01; // m^2
    projectile.coliderRadius = 20.0; // pixels
    projectile.decay = 3.0;

    #ifndef NDEBUG
    SetTraceLogLevel(LOG_DEBUG);
    #endif

    while (!WindowShouldClose()) {
        projectile.Tick();
        if (CheckCollisionCircles(target.position, target.coliderRadius, projectile.position, projectile.coliderRadius)) {
            ColisionHandler(true, target, projectile);       
        } else {
            ColisionHandler(false, target, projectile);
        }
        
        target.Tick();
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        #ifndef NDEBUG
        DrawCircleV(target.safeZone.position, target.safeZone.radius, RED);
        DrawCircleV(target.position, target.coliderRadius, GOLD);
        DrawCircleV(projectile.position, projectile.coliderRadius, BLUE);
        DrawLineEx(projectile.position, Vector2Add(projectile.position, projectile.forceDir), 3, BLACK);
        DrawLineEx(target.position, Vector2Add(target.position, target.forceDir), 3, BLACK);
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