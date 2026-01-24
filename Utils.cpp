#include "Utils.h"
#include "Classes.h"
#include <random>
#include <iostream>
#include <limits>
#include <vector>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::unique_ptr;
using std::make_unique;
using std::vector;

int random_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void print_stats(const Character* player) {
    if (player == nullptr) return;

    cout << "\n----------------------------------------\n";
    cout << "    PLAYER STATS (Mediocre at best)  \n";
    cout << "----------------------------------------\n";
    cout << "Name:  " << player->get_name() << "\n";
    cout << "Level: " << player->get_level() << "\n";
    cout << "HP:    " << player->get_HP() << " (Try to keep this above 0)\n";
    cout << "MP:    " << player->get_MP() << "\n";
    cout << "Power: " << player->get_power() << "\n";
    cout << "Gold:  " << player->get_coins() << "\n";
    cout << "EXP:   " << player->get_exp() << " / " << player->get_exp_to_next_level() << "\n";
    cout << "----------------------------------------\n";
}

void print_tutorial() {
    cout << "\n=================================================\n";
    cout << "           WELCOME TO DAGGERS & FLIPFLOPS        \n";
    cout << "=================================================\n";
    cout << "GOAL: Climb as many floors as possible in the Endless Tower.\n";
    cout << "\nMECHANICS:\n";
    cout << " * BATTLES:  Turn-based combat. Use your weapon or items.\n";
    cout << " * SHOP:     Buy potions to survive and better weapons to kill.\n";
    cout << " * EVENTS:   Random encounters (Wildcards) can bless or curse you.\n";
    cout << " * DEATH:    Is permanent. Don't die.\n";
    cout << "\nTIPS:\n";
    cout << " - Mages need MP. Warriors need HP. Thieves need luck.\n";
    cout << " - Use potions BEFORE you reach 0 HP.\n";
    cout << " - Different weapons have special effects for different classes.\n";
    cout << "=================================================\n\n";
    
    cout << "Press ENTER to start your suffering...";
    cin.get();
}

void change_player_class(unique_ptr<Character>& player) {
    
    string currentClass = player->get_class_name();
    
    vector<string> candidates;
    for (const string& className : all_classes) {
        if (className != currentClass) {
            candidates.push_back(className);
        }
    }

    if (candidates.empty()) {
        cout << "Error: No other classes available to switch to.\n";
        return;
    }
    
    int randomIndex = random_int(0, candidates.size() - 1);
    string newClassName = candidates[randomIndex];

    unique_ptr<Character> newPlayer;

    if (newClassName == "Warrior") newPlayer = make_unique<Warrior>(player->get_name());
    else if (newClassName == "Mage") newPlayer = make_unique<Mage>(player->get_name());
    else if (newClassName == "Thief") newPlayer = make_unique<Thief>(player->get_name());
    else if (newClassName == "Archer") newPlayer = make_unique<Archer>(player->get_name());
    else if (newClassName == "Normie") newPlayer = make_unique<Normie>(player->get_name());
    else {
        cout << "Error: Unknown class generated: " << newClassName << ".\n";
        return;
    }

    cout << "\n*** TRANSFORMING INTO " << newClassName << " ***\n";
    newPlayer->transfer_player(*player); 
    player = move(newPlayer);
    
    cout << "Transformation complete! Check your new stats.\n";
}


string get_string(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;  
        if (!getline(cin, line)) {
            cin.clear();
            continue; 
        }
        if (line.empty()) {
            continue; 
        }
        return line;
    }
}

int get_int(const string& prompt) {
    while (true) {
        string input = get_string(prompt);

        try {
            int result = stoi(input);
            return result;
        } 
        catch (const std::invalid_argument&) {
            cout << "Error: That's not a number. Try again.\n";
        }
        catch (const std::out_of_range&) {
            cout << "Error: Number too large (or small). Be reasonable.\n";
        }
    }
}

string lowerecase(string& str){
    for (auto& x : str) {
        x = tolower(x);
    }
    return str;
}
