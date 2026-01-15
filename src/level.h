#pragma once

class Level {
    public:
        virtual void load() {};
        virtual void unload() {};
        virtual void loop() {};
};

class LevelManager {
    public:
        inline static Level* currentLevel = nullptr;
        static void changeLevel(Level* newLevel);
        static void unloadCurrentLevel();
};
