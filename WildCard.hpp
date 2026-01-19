#ifndef WILDCARD_H
#define WILDCARD_H

#include "Encounter.h"
#include "Enemy.h"
#include "Utils.h"
#include <iostream>

using std::cout;
using std::cin;

class WildCard : public Encounter {
public:
    void run(Character* player) override {
        cout << "You stumble upon something...\n";
        int roll = random_int(1, 3);
        if (roll == 1) {
            cout << "It's a Trap! Obviously. (Damage taken)\n";
            player->damage(player->get_HP() * 0.2);
        } else if (roll == 2) {
            cout << "Ancient shrine. Full Heal.\n";
            player->heal(1000);
        } else {
            cout << "Found 50 coins. Don't spend it all in one place.\n";
            player->new_coins(50);
        }
    }
};

#endif