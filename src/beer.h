#pragma once
#include <string>
#include <vector>
#include "beer_effect.h"

class Beer {
public:
	Beer(const std::string& name, const std::string& imageName, float drinkTime, int price, std::vector<BeerEffect> effects)
		: name(name), imageName(imageName), drinkTime(drinkTime), price(price), effects(effects) {}

	void addEffect(const BeerEffect& effect) {
		effects.push_back(effect);
	}

	std::string getName() const { return name; }
	std::string getImageName() const { return imageName; }
	float getDrinkTime() const { return drinkTime; }
	int getPrice() const { return price; }
	const std::vector<BeerEffect>& getEffects() const { return effects; }

private:
	std::string name;
	std::string imageName;
	float drinkTime;
	int price;
	std::vector<BeerEffect> effects;
};

inline std::vector<Beer> beers = {
	Beer("Carlsberg", "assets/carlsberg.png", 7, 4, {
		BeerEffect(EffectType::FASTER_DRINK, EffectTrigger::CONTINUOUS, 1.25),
		BeerEffect(EffectType::INVERTED_AIM, EffectTrigger::CONTINUOUS, 0)
	}),
	Beer("Zubr", "assets/cel.png", 8, 2, {
		BeerEffect(EffectType::WOBBLY_AIM, EffectTrigger::CONTINUOUS, 1.75),
		BeerEffect(EffectType::FASTER_DRINK, EffectTrigger::CONTINUOUS, 1.50)
	}),
	Beer("Tyskie", "assets/tyskie.png", 5, 1, {}),
	Beer("Zywiec", "assets/zywiec.png", 6, 8, {
		BeerEffect(EffectType::CROSSHAIR, EffectTrigger::AT_50_PERCENT, 0)
	}),
	Beer("Zywiec ciemne", "assets/zywiec_ciemne.png", 10, 5, {
		BeerEffect(EffectType::SLOWER_DRINK, EffectTrigger::CONTINUOUS, 0.75),
		BeerEffect(EffectType::ACCURACY_BOOST, EffectTrigger::CONTINUOUS, 1.50)
	}),
	Beer("Perla export", "assets/perla_export.png", 10, 2, {
		BeerEffect(EffectType::SLOWER_SPEED_ADJUSTMENT, EffectTrigger::ON_START, 0.9)
	}),
};
