#pragma once
#include <array>
#include <string>
#include <raylib.h>
#include "level.h"
#include "inventory_manager.h"
#include "utils.h"
#include "town_map.h"

class Inventory : public Level {
	public:
		void load() override;
		void unload() override;
		void loop() override;

private:
	Texture2D inventoryBackground;
	std::unordered_map<std::string, Texture2D> beerTextures;
};