#pragma once
#include <array>
#include <string>
#include <raylib.h>
#include "level.h"

class Inventory : public Level {
	public:
		void load() override;
		void unload() override;
		void loop() override;

private:
	Texture2D inventoryBackground;
	//TODO: zaimplementowac klase "piwo" zawierajaca nazwe, zdjecie, cena i perki
	// polaczone z InventoryManager i Shop
	std::array<std::pair<Texture2D, std::string>, 6> beers;
};