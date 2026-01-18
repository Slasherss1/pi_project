#pragma once
#include <array>
#include <raylib.h>
#include "level.h"

class Shop : public Level {
	public:
		void load() override;
		void unload() override;
		void loop() override;

	private:
		Texture2D shopInterior;
		//TODO: zaimplementowac klase "piwo" zawierajaca nazwe, zdjecie, cena i perki
		// polaczone z InventoryManager
		std::array<std::pair<Texture2D, std::string>, 6> beers;

		void showBeersWithInfo();
};