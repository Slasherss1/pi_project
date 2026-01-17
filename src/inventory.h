#pragma once
#include <raylib.h>
#include "level.h"

class Inventory : public Level {
	public:
		void load() override;
		void unload() override;
		void loop() override;

private:
	Texture2D inventoryBackground;

};