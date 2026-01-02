#include <iostream>
#include <raylib.h>
#include "target.h"

using namespace std;
int main() {
    cout << "Hello, World!" << endl;
    InitWindow(800, 600, "Hello Raylib");
    
    Target target;
    target.texture = LoadTexture("assets/cel.png");

    while (!WindowShouldClose()) {

        target.Tick();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Raylib!", 190, 200,20, LIGHTGRAY);

        target.Draw();

        EndDrawing();
    }

    UnloadTexture(target.texture);

    CloseWindow();
    return 0;
}