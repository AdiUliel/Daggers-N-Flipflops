#include "Utils.h"
#include <random>
#include <iostream>
#include <limits>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

int random_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void print_stats(Character* player) {
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
            int result = std::stoi(input);
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