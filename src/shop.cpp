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
	//InventoryManager::getInstance().addMoney(5);
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
	
	showBeersInfo(beers, true);

	EndDrawing();
}
