#include "Utils.h"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

int random_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void print_stats(Character* player) {
    if (player == nullptr) return; // הגנה מקריסה

    cout << "\n----------------------------------------\n";
    cout << "       PLAYER STATS (Mediocre at best)  \n";
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