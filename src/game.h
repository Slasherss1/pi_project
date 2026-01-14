#pragma once
#include <raylib.h>

enum class GameState { START, SETTINGS, GAME };
enum class GameDifficulty { EASY, HARD };

class Game {
public:
    Game();
    ~Game();
    void Run();

private:
    GameState state;
    GameDifficulty difficulty;
    Texture2D menuTexture;
    Texture2D settingsTexture;
    Texture2D whiteMan;
    Texture2D redMan;
    void DrawStartMenu();
    void DrawSettingsMenu();
    void DrawGame();
};
