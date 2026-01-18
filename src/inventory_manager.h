#pragma once
#include <string>
#include <vector>
#include <raylib.h>

enum GameDifficulty { EASY, HARD };
// nazwa pliku do zapisu stanu gry w tym miejscu,
// poniewaz jest uzywana w kilku miejscach.
// jest na wierzchu, aby latwiej bylo zmienic w przyszlosci
static const char* SAVE_FILE = "save.dat";

// klasa typu singleton
class InventoryManager {
public:
    static InventoryManager& getInstance() {
        static InventoryManager instance;
        return instance;
    }

    InventoryManager(const InventoryManager&) = delete;
    void operator=(const InventoryManager&) = delete;


    // TODO: zaimplementowac klase "piwo" zawierajaca nazwe, zdjecie i perki
    void addBeer(const std::string& beer);
	bool removeBeer(const std::string& beer);

	void addMoney(int amount);
	void removeMoney(int amount);

	int getWallet() const;
    std::vector<std::string> getBeers() const;

    GameDifficulty getDifficulty() const;
	void setDifficulty(GameDifficulty diff);

	bool saveInventory(const std::string& filename) const;
	bool loadInventory(const std::string& filename);
	void resetInventory();

private:
    InventoryManager() : wallet(0), difficulty(GameDifficulty::EASY), beers({}) { }

    int wallet;
    std::vector<std::string> beers;
    GameDifficulty difficulty;
};