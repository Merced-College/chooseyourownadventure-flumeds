#include "Weapon.h"

// Constructor
Weapon::Weapon(string name, string description, int durability,
               vector<string> actions, int damage)
    : name(name), description(description),
      durability(durability), actions(actions), damage(damage) {}

// Getters
string Weapon::getName() const {
    return name;
}

string Weapon::getDescription() const {
    return description;
}

int Weapon::getDurability() const {
    return durability;
}

vector<string> Weapon::getActions() const {
    return actions;
}

int Weapon::getDamage() const {
    return damage;
}

// Setter
void Weapon::setDurability(int durability) {
    this->durability = durability;
}

// Method to use weapon
void Weapon::use() {
    if (durability > 0) {
        durability--;
    }
}