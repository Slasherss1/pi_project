#include <iostream>
#include <raylib.h>

using namespace std;
int main() {
    cout << "Hello, World!" << endl;
    InitWindow(800, 600, "Hello Raylib");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Raylib!", 190, 200,20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}