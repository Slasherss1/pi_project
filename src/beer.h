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

