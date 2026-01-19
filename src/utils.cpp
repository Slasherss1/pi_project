#include "utils.h"
#include "beer.h"
#include "inventory_manager.h"
#include "beer_registry.h"

bool TextButton(const char* text, Vector2 pos, int fontSize, Color normal, Color hover) {
    Vector2 size = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
    Rectangle rec = { pos.x, pos.y, size.x, size.y };

    bool isHovered = CheckCollisionPointRec(GetMousePosition(), rec);
    DrawText(text, pos.x, pos.y, fontSize, isHovered ? hover : normal);

    return isHovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

bool TextureButton(Texture2D texture, Vector2 position, Color tint) {
    Rectangle rect = { position.x, position.y, (float) texture.width, (float) texture.height };
    DrawTexture(texture, (int) position.x, (int) position.y, tint);
    return CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

float GetCenteredXInBounds(const char* text, int fontSize, float left, float right) {
    int textWidth = MeasureText(text, fontSize);
    float boundsWidth = right - left;
    return left + (boundsWidth - textWidth) / 2.0f;
}

float GetCenteredX(const char* text, int fontSize) {
    return GetCenteredXInBounds(text, fontSize, 0, GetScreenWidth());
}

void DrawBackground(Texture2D texture) {
    DrawTexturePro(
        texture,
        {0, 0, (float) texture.width, (float) texture.height},
        {0, 0, (float) GetScreenWidth(), (float) GetScreenHeight()},
        {0, 0},
        0.0f,
        WHITE
    );
}

std::unordered_map<std::string, Texture2D> loadBeerTextures() {
    std::unordered_map<std::string, Texture2D> beerTextures;
    for (const auto& beer : BeerRegistry::getInstance().getAllBeers()) {
        beerTextures[beer.getName()] = LoadTexture(beer.getImageName().c_str());
    }
    return beerTextures;
}

void unloadBeerTextures(std::unordered_map<std::string, Texture2D>& beerTextures) {
    for (auto& [beerName, beerTexture] : beerTextures) {
        UnloadTexture(beerTexture);
    }
    beerTextures.clear();
}

void showBeersInfo(std::unordered_map<std::string, Texture2D> &beerTextures, bool showMore) {
    InventoryManager& inventory = InventoryManager::getInstance();
    const std::vector<Beer>& beers = BeerRegistry::getInstance().getAllBeers();

    // Dane do rownego rysowania
    const int BEERS_PER_ROW = 3;
    const int START_Y = 150;
    const int ROW_SPACING = 250;
    const int BEER_SPACING = 800 / (BEERS_PER_ROW + 1);

	for (int i = 0; i < beers.size(); i++) {
		int row = i / BEERS_PER_ROW;
		int col = i % BEERS_PER_ROW;
		Texture2D currentTexture = beerTextures[beers[i].getName()];

		// Pozycje rysowania
		int x = BEER_SPACING * (col + 1) - currentTexture.width / 2;
		int y = START_Y + row * ROW_SPACING;

		bool clicked = TextureButton(currentTexture, { (float)x, (float)y }, WHITE);

		// Rysowanie nazwy i ilosci
		std::string beerName = beers[i].getName() + " x" + std::to_string(inventory.countBeer(beers[i].getName()));
		int nameWidth = MeasureText(beerName.c_str(), 18);
		int nameX = BEER_SPACING * (col + 1) - nameWidth / 2;
		int nameY = y + currentTexture.height + 5;
		DrawText(beerName.c_str(), nameX, nameY, 18, WHITE);

        if (showMore) {
			// Rysowanie ceny
            int currentPrice = beers[i].getPrice();

		    std::string priceText = "Cena: " + std::to_string(currentPrice) + "zl";
		    int priceWidth = MeasureText(priceText.c_str(), 16);
		    int priceX = BEER_SPACING * (col + 1) - priceWidth / 2;
		    int priceY = nameY + 25;

		    DrawText(priceText.c_str(), priceX, priceY, 16, WHITE);

			// Wyswietlanie efektow
			const auto& effects = beers[i].getEffects();
			int effectY = priceY + 20;
			int effectFontSize = 12;
			
			for (const auto& effect : effects) {
                std::string effectText = GetEffectDescription(effect);
				int effectWidth = MeasureText(effectText.c_str(), effectFontSize);
				int effectX = BEER_SPACING * (col + 1) - effectWidth / 2;
				
				DrawText(effectText.c_str(), effectX, effectY, effectFontSize, YELLOW);
				effectY += effectFontSize + 3;
			}

		    if (clicked) {
			    if (inventory.getWallet() >= currentPrice) {
				    inventory.addBeer(beers[i].getName());
				    inventory.removeMoney(currentPrice);
			    }
		    }
        }
	}
}

std::string GetKeycodePrintableName(KeyboardKey key) {
    switch (key) {
        case KEY_SPACE: return "SPACJA";
        case KEY_ENTER: return "ENTER";
        case KEY_ESCAPE: return "ESCAPE";
        case KEY_LEFT: return "LEWO";
        case KEY_RIGHT: return "PRAWO";
        case KEY_UP: return "GORA";
        case KEY_DOWN: return "DOL";
        default:
            // For alphanumeric keys, we can convert directly
            if ((key >= KEY_A && key <= KEY_Z) || (key >= KEY_ZERO && key <= KEY_NINE)) {
                return std::string(1, (char)key);
            }
            return "UNKNOWN KEY";
    }
}