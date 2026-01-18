#pragma once
#include <unordered_map>
#include <raylib.h>
#include "level.h"

class Shop : public Level {
	public:
		void load() override;
		void unload() override;
		void loop() override;

	private:
		Texture2D shopInterior;
		std::unordered_map<std::string, Texture2D> beerTextures;
};