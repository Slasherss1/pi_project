#include "drinkMeter.h"
#include "beer_effect.h"
#include "inventory_manager.h"
#include "utils.h"
#include <raylib.h>

#define DRINK_METER_WIDTH 64.0f
#define DRINK_METER_HEIGHT 256.0f

void DrinkMeter::sip() {
    float sipMultiplier = 1.0f;
    const BeerEffect* faster = beerByNameHasEffect(InventoryManager::getInstance().getChosenBeer(), FASTER_DRINK);
    if (faster) {
        sipMultiplier *= faster->value;
    }
    const BeerEffect* slower = beerByNameHasEffect(InventoryManager::getInstance().getChosenBeer(), SLOWER_DRINK);
    if (slower) {
        sipMultiplier *= slower->value;
    }
    currentLevel -= sipSize * sipMultiplier;
    if (currentLevel < 0.0f) {
        currentLevel = 0.0f;
    }
}

void DrinkMeter::reset() {
    currentLevel = 1.0f;
}

void DrinkMeter::draw() {
    DrawRectangleGradientV(
        GetScreenWidth() - DRINK_METER_WIDTH, 
        GetScreenHeight()/2.0+DRINK_METER_HEIGHT/2.0-DRINK_METER_HEIGHT*currentLevel, 
        DRINK_METER_WIDTH, 
        DRINK_METER_HEIGHT*currentLevel, 
        {0xda,0x62,0x0a,0xff}, 
        {0xfe, 0xcd, 0x3b, 0x90}
    );
    DrawRectangleLinesEx(
        {
            GetScreenWidth() - DRINK_METER_WIDTH,
            GetScreenHeight()/2.0f-DRINK_METER_HEIGHT/2,
            DRINK_METER_WIDTH,
            DRINK_METER_HEIGHT
        },
        5.0,
        BLACK
    );
}