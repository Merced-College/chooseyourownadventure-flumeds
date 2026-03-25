// Hero.h
#ifndef HERO_H
#define HERO_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Hero {
private:
    string name;
    string description;
    int health;
    int maxHealth;
    vector<string> abilities;
    vector<string> inventory;

public:
    // Constructor
    Hero(string n = "Hero", string d = "A brave adventurer", int h = 100, vector<string> a = {});

    // Getters
    string getName() const;
    string getDescription() const;
    int getHealth() const;
    int getMaxHealth() const;
    vector<string> getAbilities() const;
    vector<string> getInventory() const;

    // Methods
    void addItem(const string& item);
    void removeItem(int index);
    void displayInventory() const;
    void takeDamage(int dmg);
    void heal(int amount);
    bool isAlive() const;
    void displayStatus() const;
    bool hasItem(const string& item) const;
};

#endif