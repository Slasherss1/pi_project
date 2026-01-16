#include <raylib.h>
#include "menu.h"
#include "level.h"

// using namespace std;
int main() {
    InitWindow(800, 600, "Flanki");
	SetTargetFPS(60);

    LevelManager::changeLevel(new MainMenu());
    while (!WindowShouldClose())
        LevelManager::currentLevel->loop();

    LevelManager::unloadCurrentLevel();

    CloseWindow();
    return 0;
}