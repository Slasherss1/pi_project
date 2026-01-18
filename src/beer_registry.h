#pragma once
#include <vector>
#include <string>
#include "beer.h"

class BeerRegistry {
public:
	static BeerRegistry& getInstance() {
		static BeerRegistry instance;
		return instance;
	}

	const std::vector<Beer>& getAllBeers() const { return beers; }
	const Beer* getBeerByName(const std::string& name) const;
	size_t getBeerCount() const { return beers.size(); }

private:
	BeerRegistry();
	BeerRegistry(const BeerRegistry&) = delete;
	void operator=(const BeerRegistry&) = delete;

	std::vector<Beer> beers;
};
