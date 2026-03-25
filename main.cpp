#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include "LinkedList.h"
#include "Enemy.h"
#include "Weapon.h"

using namespace std;

void introduction() {
    cout << "==========================================\n";
    cout << "Welcome to the Castle Adventure!\n";
    cout << "Navigate the rooms, collect weapons, and survive.\n";
    cout << "==========================================\n\n";
}

// Fight enemy using weapon if available, otherwise bare hands
bool fightEnemy(Enemy& enemy, vector<Weapon>& inventory) {
    cout << "\n*** ENEMY ENCOUNTERED ***\n";
    cout << "Enemy: " << enemy.getName() << "\n";
    cout << "Description: " << enemy.getDescription() << "\n";
    cout << "Health: " << enemy.getHealth() << "\n\n";

    while (enemy.isAlive()) {
        cout << "What do you do?\n";
        cout << "1. Attack";
        if (!inventory.empty()) {
            cout << " (using " << inventory.back().getName() 
                 << ", damage: " << inventory.back().getDamage() 
                 << ", durability: " << inventory.back().getDurability() << ")";
        }
        cout << "\n2. Flee\n";
        cout << "Choose (1-2): ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            int damage;
            if (!inventory.empty() && inventory.back().getDurability() > 0) {
                damage = inventory.back().getDamage();
                inventory.back().use(); // reduce durability
                cout << "You attack with " << inventory.back().getName() << " and deal " << damage << " damage!\n";
                if (inventory.back().getDurability() == 0) {
                    cout << inventory.back().getName() << " has broken!\n";
                    inventory.pop_back();
                }
            } else {
                damage = rand() % 10 + 5; // bare hands, weaker
                cout << "You attack with bare hands and deal " << damage << " damage!\n";
            }

            enemy.setHealth(enemy.getHealth() - damage);
            if (enemy.isAlive()) {
                cout << enemy.getName() << " has " << enemy.getHealth() << " HP left.\n\n";
            } else {
                cout << "You defeated the " << enemy.getName() << "!\n\n";
                return true;
            }
        } else if (choice == 2) {
            cout << "You flee from the " << enemy.getName() << "!\n\n";
            return false;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return true;
}

int main() {
    LinkedList castleRooms;
    ifstream file("rooms.csv");
    string line;

    map<string, string> roomEnemyName;

    // Load rooms from rooms.csv
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string name, description, actionsStr, item, enemyName;
            vector<string> actions;

            getline(ss, name, ',');
            getline(ss, description, ',');
            getline(ss, actionsStr, ',');
            getline(ss, item, ',');
            getline(ss, enemyName);

            stringstream actionStream(actionsStr);
            string action;
            while (getline(actionStream, action, ';')) {
                actions.push_back(action);
            }

            Room newRoom(name, description, actions, item);
            castleRooms.addRoom(newRoom);

            if (!enemyName.empty()) {
                roomEnemyName[name] = enemyName;
            }
        }
        file.close();
    } else {
        cout << "Unable to open rooms.csv" << endl;
        return 1;
    }

    // Load enemies from enemies.csv
    map<string, Enemy> enemies;
    ifstream enemyFile("enemies.csv");
    if (enemyFile.is_open()) {
        while (getline(enemyFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string name, description, healthStr, abilitiesStr, roomIDStr;
            vector<string> abilities;

            getline(ss, name, ',');
            getline(ss, description, ',');
            getline(ss, healthStr, ',');
            getline(ss, abilitiesStr, ',');
            getline(ss, roomIDStr);

            stringstream abilityStream(abilitiesStr);
            string ability;
            while (getline(abilityStream, ability, ';')) {
                abilities.push_back(ability);
            }

            int health = stoi(healthStr);
            int roomID = stoi(roomIDStr);
            Enemy e(name, description, health, abilities, roomID);
            enemies.emplace(name, e);
        }
        enemyFile.close();
    } else {
        cout << "Unable to open enemies.csv" << endl;
        return 1;
    }

    introduction();

    // Player weapon inventory
    vector<Weapon> inventory;

    // Game loop
    auto current = castleRooms.getHead();
    while (current != nullptr) {
        Room& room = current->room;

        cout << "=== " << room.getName() << " ===\n";
        cout << room.getDescription() << "\n";

        // Show weapon item in room and offer to pick it up
        if (!room.getItem().empty()) {
            cout << "You notice a weapon here: " << room.getItem() << "\n";
            cout << "Pick it up? (1 = Yes, 2 = No): ";
            int pick;
            cin >> pick;
            if (pick == 1) {
                // Create weapon with default stats based on item name
                Weapon w(room.getItem(), "A weapon found in the castle.", 5, {"Attack"}, 20);
                inventory.push_back(w);
                room.setItem(""); // remove from room
                cout << room.getItem().empty() ? "" : "";
                cout << "You picked up the " << w.getName() << "! (damage: " << w.getDamage() << ", durability: " << w.getDurability() << ")\n";
            }
        }

        // Show inventory
        if (!inventory.empty()) {
            cout << "Inventory: ";
            for (auto& w : inventory) {
                cout << w.getName() << " (dur:" << w.getDurability() << ") ";
            }
            cout << "\n";
        }

        // Fight enemy if present
        string roomName = room.getName();
        if (roomEnemyName.count(roomName) && enemies.count(roomEnemyName[roomName])) {
            Enemy& enemy = enemies.at(roomEnemyName[roomName]);
            if (enemy.isAlive()) {
                fightEnemy(enemy, inventory);
            }
        }

        cout << "\nWhat do you do?\n";

        bool leaveRoom = false;
        while (!leaveRoom) {
            int actionNum = 1;
            for (const auto& action : room.getActions()) {
                cout << actionNum++ << ". " << action << "\n";
            }

            int choice;
            cout << "Choose an action (1-" << room.getActions().size() << "): ";
            cin >> choice;

            if (choice < 1 || choice > (int)room.getActions().size()) {
                cout << "Invalid choice. Try again.\n\n";
                continue;
            }

            string chosen = room.getActions()[choice - 1];
            cout << "\n> " << chosen << "\n";

            if (choice == (int)room.getActions().size()) {
                cout << "You leave the " << room.getName() << " behind.\n\n";
                leaveRoom = true;
            } else {
                cout << "You " << chosen << " in the " << room.getName() << ".\n";
                cout << "Interesting... but there's more to do here.\n\n";
            }
        }

        current = current->next;
    }

    cout << "You have reached the end of your adventure!\n";
    return 0;
}
