#include <iostream>
#include <raylib.h>
#include "game.h"

using namespace std;
int main() {
    InitWindow(800, 600, "Flanki");
    Game().Run();
    return 0;
}