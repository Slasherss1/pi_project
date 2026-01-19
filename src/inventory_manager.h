#pragma once
#include <string>
#include <vector>
#include <raylib.h>

enum GameDifficulty { EASY, HARD };
// nazwa pliku do zapisu stanu gry w tym miejscu,
// poniewaz jest uzywana w wielu plikach.
// jest na wierzchu, a nie w funkcji samej w sobie, aby latwiej bylo zmienic w przyszlosci
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

    void addBeer(const std::string& beer);
	bool removeBeer(const std::string& beer);
	int countBeer(const std::string& beer) const;

	void addMoney(int amount);
	void removeMoney(int amount);

	int getWallet() const;
    std::vector<std::string> getBeers() const;

    GameDifficulty getDifficulty() const;
	void setDifficulty(GameDifficulty diff);

	bool saveInventory(const std::string& filename) const;
	bool loadInventory(const std::string& filename);
	void resetInventory();

    void setChosenBeer(const std::string& beer);
    std::string getChosenBeer() const;

private:
    InventoryManager() : wallet(0), difficulty(GameDifficulty::EASY), beers({}) { }

    int wallet;
    std::vector<std::string> beers;
    GameDifficulty difficulty;
    std::string chosenBeer;
};