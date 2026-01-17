#pragma once
#include <raylib.h>
#include "level.h"

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