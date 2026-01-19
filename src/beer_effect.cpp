#include "beer_effect.h"

std::string GetEffectTypeName(EffectType type) {
    switch (type) {
        case ACCURACY_BOOST: return "Zwiekszona celnosc";
        case CROSSHAIR: return "Celownik";
        case WOBBLY_AIM: return "Trzesacy sie celownik";
        case SLOWER_DRINK: return "Wolniejsze picie";
        case SLOWER_SPEED_ADJUSTMENT: return "Wolniejsza regulacja sily";
        case FASTER_DRINK: return "Szybsze picie";
        case INVERTED_AIM: return "Odwrocony celownik";
        default: return "Nieznany efekt";
    }
}

std::string GetEffectTriggerName(EffectTrigger trigger) {
    switch (trigger) {
        case ON_START: return "na start";
        case AT_25_PERCENT: return "po 25%";
        case AT_50_PERCENT: return "po 50%";
        case AT_75_PERCENT: return "po 75%";
        case CONTINUOUS: return "caly czas";
        default: return "nieznany";
    }
}

std::string GetEffectDescription(const BeerEffect& effect) {
    return GetEffectTypeName(effect.type) + " (" + GetEffectTriggerName(effect.trigger) + ")";
}