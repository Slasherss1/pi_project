#include <string>
#include "shop.h"
#include "utils.h"
#include "town_map.h"
#include "inventory_manager.h"

static const char* SHOP_NAME = "Studenciak";
static const char* SHOP_INSTRUCTION = "Nacisnij SPACJE, aby wyjsc";
static const char* WALLET_STATUS = "Portfel: ";

void Shop::load() {
	// na potrzeby testow
	InventoryManager::getInstance().addMoney(5);
	shopInterior = LoadTexture("assets/studenciak.png");
	beers = { {
		{LoadTexture("assets/carlsberg.png"),		"Carlsberg"},
		{LoadTexture("assets/cel.png"),				"Zubr"},
		{LoadTexture("assets/zywiec.png"),			"Zywiec"},
		{LoadTexture("assets/zywiec_ciemne.png"),	"Zywiec ciemne"},
		{LoadTexture("assets/tyskie.png"),			"Tyskie"},
		{LoadTexture("assets/perla_export.png"),	"Perla export"}
	} };
}

void Shop::unload() {
	UnloadTexture(shopInterior);
	for (const auto& beer : beers) {
		UnloadTexture(beer.first);
	}

	InventoryManager::getInstance().saveInventory(SAVE_FILE);
}

void Shop::loop() {
	if (IsKeyDown(KEY_SPACE)) {
		LevelManager::changeLevel(new TownMap());
		// return, bo kod ladowal sie dalej mimo zmiany levelu
		return;
	}

	std::string wallet = "Portfel: " + std::to_string(InventoryManager::getInstance().getWallet()) + "zl";

	BeginDrawing();

	DrawTexture(shopInterior, 0, 0, WHITE);
	DrawText(SHOP_NAME, GetCenteredX(SHOP_NAME, 70), 20, 70, YELLOW);
	DrawText(SHOP_INSTRUCTION, GetScreenWidth() - MeasureText(SHOP_INSTRUCTION, 20) - 2, GetScreenHeight() - 22, 20, WHITE);
	DrawText(wallet.c_str(), GetCenteredX(wallet.c_str(), 20), 90, 20, WHITE);
	
	showBeersWithInfo();

	EndDrawing();
}

void Shop::showBeersWithInfo() {
	InventoryManager& inventory = InventoryManager::getInstance();
	
	// Dane do rownego rysowania
	const int BEER_PRICE = 1;
	const int BEERS_PER_ROW = 3;
	const int START_Y = 150;
	const int ROW_SPACING = 250;
	const int BEER_SPACING = 800 / (BEERS_PER_ROW + 1);
	
	for (int i = 0; i < beers.size(); i++) {
		int row = i / BEERS_PER_ROW;
		int col = i % BEERS_PER_ROW;
		
		int x = BEER_SPACING * (col + 1) - beers[i].first.width / 2;
		int y = START_Y + row * ROW_SPACING;
		
		bool clicked = TextureButton(beers[i].first, {(float)x, (float)y}, WHITE);
		
		std::string beerName = beers[i].second + " x" + std::to_string(inventory.countBeer(beers[i].second));
		int nameWidth = MeasureText(beerName.c_str(), 18);
		int nameX = BEER_SPACING * (col + 1) - nameWidth / 2;
		int nameY = y + beers[i].first.height + 5;
		DrawText(beerName.c_str(), nameX, nameY, 18, WHITE);
		
		// Rysuj cene na samym dole uzywajac TextButton (zeby tez byla klikalna)
		std::string priceText = "Cena: " + std::to_string(BEER_PRICE) + "zl";
		int priceWidth = MeasureText(priceText.c_str(), 16);
		int priceX = BEER_SPACING * (col + 1) - priceWidth / 2;
		int priceY = nameY + 25;
		
		DrawText(priceText.c_str(), (float)priceX, (float)priceY, 16, WHITE);
		
		// Zakup piwa jesli kliknieto na teksture
		if (clicked) {
			if (inventory.getWallet() >= BEER_PRICE) {
				inventory.addBeer(beers[i].second);
				inventory.removeMoney(BEER_PRICE);
			}
		}
	}
}
