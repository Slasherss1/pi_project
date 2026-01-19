#include <string>
#include "inventory_manager.h"
#include "utils.h"
#include "town_map.h"
#include "shop.h"
#include "beer.h"

static const char* SHOP_NAME = "Studenciak";
static const char* SHOP_INSTRUCTION = "Nacisnij SPACJE, aby wyjsc";
static const char* WALLET_STATUS = "Portfel: ";

void Shop::load() {
	// na potrzeby testow
	//InventoryManager::getInstance().addMoney(5);
	shopInterior = LoadTexture("assets/studenciak.png");
	beerTextures = loadBeerTextures();
}

void Shop::unload() {
	UnloadTexture(shopInterior);
	unloadBeerTextures(beerTextures);

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
	
	showBeersInfo(beerTextures, true);

	EndDrawing();
}
