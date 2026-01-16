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
        Texture2D whiteMan;
        Texture2D redMan;
        Texture2D settingsBackground;
        GameDifficulty difficulty; // TODO: Przenieść do innej klasy
        void DrawSettingsOptions();
};

#ifndef NDEBUG
class DebugChooserMenu : public Level {
    public:
        void load() override;
        void unload() override;
        void loop() override;
};
#endif