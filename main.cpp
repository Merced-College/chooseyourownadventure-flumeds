#include <fstream>
#include <sstream>
#include <map>
#include "LinkedList.h"
#include "Enemy.h"

void introduction() {
    cout << "Welcome to the Castle Adventure!\n";
    cout << "You will navigate through various rooms in the castle, encountering challenges and making decisions that will determine your path.\n";
    cout << "Choose your actions wisely. Let's start your journey!\n\n";
}

bool fightEnemy(Enemy& enemy) {
    cout << "\n*** ENEMY ENCOUNTERED ***\n";
    cout << enemy.toString() << "\n";

    while (enemy.isAlive()) {
        cout << "What do you do?\n";
        cout << "1. Attack\n";
        cout << "2. Flee\n";
        cout << "Choose (1-2): ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            int damage = rand() % 20 + 10;
            enemy.setHealth(enemy.getHealth() - damage);
            cout << "You attack and deal " << damage << " damage!\n";
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
        cout << "Unable to open file" << endl;
        return 1;
    }

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

    auto current = castleRooms.getHead();
    while (current != nullptr) {
        cout << "=== " << current->room.getName() << " ===\n";
        cout << current->room.getDescription() << "\n";
        if (!current->room.getItem().empty()) {
            cout << "You notice an item here: " << current->room.getItem() << "\n";
        }

        string roomName = current->room.getName();
        if (roomEnemyName.count(roomName) && enemies.count(roomEnemyName[roomName])) {
            Enemy& enemy = enemies.at(roomEnemyName[roomName]);
            if (enemy.isAlive()) {
                fightEnemy(enemy);
            }
        }

        cout << "\nWhat do you do?\n";

        bool leaveRoom = false;
        while (!leaveRoom) {
            int actionNum = 1;
            for (const auto& action : current->room.getActions()) {
                cout << actionNum++ << ". " << action << "\n";
            }

            int choice;
            cout << "Choose an action (1-" << current->room.getActions().size() << "): ";
            cin >> choice;

            if (choice < 1 || choice > (int)current->room.getActions().size()) {
                cout << "Invalid choice. Try again.\n\n";
                continue;
            }

            string chosen = current->room.getActions()[choice - 1];
            cout << "\n> " << chosen << "\n";

            if (choice == (int)current->room.getActions().size()) {
                cout << "You leave the " << current->room.getName() << " behind.\n\n";
                leaveRoom = true;
            } else {
                cout << "You " << chosen << " in the " << current->room.getName() << ".\n";
                cout << "Interesting... but there's more to do here.\n\n";
            }
        }

        current = current->next;
    }

    cout << "You have reached the end of your adventure!\n";
    return 0;
}
