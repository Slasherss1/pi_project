#pragma once
#include "level.h"
#include <raylib.h>

enum class GameDifficulty { EASY, HARD };

class MainMenu : public Level {
    public:
        void load() override;
        void unload() override;
        void loop() override;

    private:
        Texture2D menuTexture;
        void DrawStartMenu();
        void DrawSettingsMenu();
        void DrawGame();
};
    
class SettingsMenu : public Level {
    public:
        void load() override;
        void unload() override;
        void loop() override;
        
    private:
        Texture2D settingsTexture;
        Texture2D freshman;
        Texture2D veteran;
        Texture2D settingsBackground;
        GameDifficulty difficulty; // TODO: Przenieść do innej klasy
        void DrawSettingsOptions();
};