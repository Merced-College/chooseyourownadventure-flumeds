// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H
 
#include <string>
#include <vector>
using namespace std;
 
class Enemy {
private:
    string name;
    string description;
    int health;
    vector<string> abilities;
    bool alive;
    int roomID;
 
public:
    Enemy(string name, string description, int health, vector<string> abilities, int roomID);
 
    // Getters
    string getName() const;
    string getDescription() const;
    int getHealth() const;
    vector<string> getAbilities() const;
    bool isAlive() const;
    int getRoomID() const;
 
    // Setters
    void setHealth(int newHealth);
    void setAlive(bool status);
 
    string toString() const;
};
 
#endif
 