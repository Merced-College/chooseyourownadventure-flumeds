// Hero.cpp
#include "Hero.h"

Hero::Hero(string n, string d, int h, vector<string> a)
    : name(n), description(d), health(h), maxHealth(h), abilities(a) {}

string Hero::getName() const { return name; }
string Hero::getDescription() const { return description; }
int Hero::getHealth() const { return health; }
int Hero::getMaxHealth() const { return maxHealth; }
vector<string> Hero::getAbilities() const { return abilities; }
vector<string> Hero::getInventory() const { return inventory; }

void Hero::addItem(const string& item) {
    if (!item.empty()) {
        inventory.push_back(item);
        cout << "[Inventory] Found: " << item << endl;
    }
}

void Hero::removeItem(int index) {
    if (index >= 0 && index < (int)inventory.size()) {
        inventory.erase(inventory.begin() + index);
    }
}

void Hero::displayInventory() const {
    cout << "Inventory: ";
    if (inventory.empty()) {
        cout << "Empty";
    } else {
        for (size_t i = 0; i < inventory.size(); ++i) {
            cout << inventory[i] << (i == inventory.size() - 1 ? "" : ", ");
        }
    }
    cout << endl;
}

void Hero::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
    cout << name << " took " << dmg << " damage! Current HP: " << health << endl;
}

void Hero::heal(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
    cout << name << " healed for " << amount << ". Current HP: " << health << endl;
}

bool Hero::isAlive() const {
    return health > 0;
}

void Hero::displayStatus() const {
    cout << "\n--- HERO STATUS ---" << endl;
    cout << "Name:   " << name << " (" << description << ")" << endl;
    cout << "Health: " << health << "/" << maxHealth << endl;
    displayInventory();
    cout << "--------------------\n" << endl;
}

bool Hero::hasItem(const string& item) const {
    for (const auto& i : inventory) {
        if (i == item) return true;
    }
    return false;
}