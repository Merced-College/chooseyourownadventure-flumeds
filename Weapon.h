#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <vector>

using namespace std;

class Weapon {
private:
    string name;
    string description;
    int durability;
    vector<string> actions;
    int damage;

public:
    // Constructor
    Weapon(string name, string description, int durability,
           vector<string> actions, int damage);

    // Getters
    string getName() const;
    string getDescription() const;
    int getDurability() const;
    vector<string> getActions() const;
    int getDamage() const;

    // Setters
    void setDurability(int durability);

    // Methods
    void use();  // reduces durability
};

#endif