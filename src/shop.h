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
		std::array<Texture2D, 6> beers;

		void showBeersWithInfo();
};