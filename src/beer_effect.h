#pragma once
#include <string>

enum EffectType {
    // Zwiekszona celnosc
    ACCURACY_BOOST,
    // Celownik
    CROSSHAIR,
    // Trzesacy sie celownik
    WOBBLY_AIM,
    // Wolniejsze picie
    SLOWER_DRINK,
    // Zmiejszona szybkosc regulacji sily
	SLOWER_SPEED_ADJUSTMENT,
    // Szybsze picie
	FASTER_DRINK,
	// Odwrócony celownik
	INVERTED_AIM
};

enum EffectTrigger {
    ON_START,
    AT_25_PERCENT,
    AT_50_PERCENT,
    AT_75_PERCENT,
    CONTINUOUS
};

struct BeerEffect {
    EffectType type;
    EffectTrigger trigger;
    // Sila efektu (np. 1.5 = +50% celnosci)
    float value;
    
    BeerEffect(EffectType t, EffectTrigger trig, float val)
        : type(t), trigger(trig), value(val) {}
};