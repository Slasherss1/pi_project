#pragma once
#include <string>
#include <raylib.h>
#include "level.h"
#include <unordered_map>

class Inventory : public Level {
	public:
		void load() override;
		void unload() override;
		void loop() override;

private:
	Texture2D inventoryBackground;
	std::unordered_map<std::string, Texture2D> beerTextures;
};