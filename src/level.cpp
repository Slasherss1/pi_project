#include "level.h"

void LevelManager::changeLevel(Level* newLevel) {
    unloadCurrentLevel();
    currentLevel = newLevel;
    if (currentLevel) {
        currentLevel->load();
    }
}

void LevelManager::unloadCurrentLevel() {
    if (currentLevel) {
        currentLevel->unload();
        delete currentLevel;
        currentLevel = nullptr;
    }
}