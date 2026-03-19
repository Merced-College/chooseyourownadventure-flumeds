// Enemy.cpp
#include "Enemy.h"
 
Enemy::Enemy(string name, string description, int health, vector<string> abilities, int roomID)
    : name(name), description(description), health(health), abilities(abilities), alive(true), roomID(roomID) {}
 
// Getters
string Enemy::getName() const { return name; }
string Enemy::getDescription() const { return description; }
int Enemy::getHealth() const { return health; }
vector<string> Enemy::getAbilities() const { return abilities; }
bool Enemy::isAlive() const { return alive; }
int Enemy::getRoomID() const { return roomID; }
 
// Setters
void Enemy::setHealth(int newHealth) {
    health = newHealth;
    if (health <= 0) {
        alive = false;
    }
}
 
void Enemy::setAlive(bool status) { alive = status; }
 
string Enemy::toString() const {
    string info = "Enemy: " + name + "\nDescription: " + description +
                  "\nHealth: " + to_string(health) +
                  "\nAlive: " + (alive ? "Yes" : "No") +
                  "\nAbilities:\n";
    for (const auto& ability : abilities) {
        info += "- " + ability + "\n";
    }
    info += "Room ID: " + to_string(roomID) + "\n";
    return info;
}