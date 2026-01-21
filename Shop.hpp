#ifndef SHOP_H
#define SHOP_H

#include "Encounter.h"
#include "Utils.h"
#include "Bow.hpp"
#include "Staff.hpp"
#include <iostream>

using std::cout;
using std::cin;

class Shop : public Encounter {
public:
    void run(Character* player) override {
        cout << "\n--- WANDERING MERCHANT ---\n";
        cout << "Merchant: 'Oh, look who survived.' (Coins: " << player->get_coins() << ")\n";
        
        cout << "1. Potion (Heal 50 HP)    - 20 Coins\n";
        cout << "2. Longbow (Thief/Archer) - 150 Coins\n";
        cout << "3. Mystic Staff (Mage)    - 100 Coins\n";
        cout << "4. Leave\n> ";
        
        int choice = get_int("> ");

        // Pot Buy
        if (choice == 1) {
            if (player->get_coins() >= 20) {
                player->new_coins(-20);
                player->heal(50);
                cout << "You chug the potion. Tastes like feet, but it heals.\n";
            } else {
                cout << "Merchant: 'No gold? Then bleed somewhere else.'\n";
            }
        } 
        // Bow Buy
        else if (choice == 2) {
            if (player->get_coins() >= 150) {
                player->new_coins(-150);
                player->equip(new Bow());
                cout << "Merchant: 'Try not to shoot yourself.'\n";
            } else {
                cout << "Merchant: 'This isn't a charity. Come back when you're rich.'\n";
            }
        }
        // Staff Buy
        else if (choice == 3) {
            if (player->get_coins() >= 100) {
                player->new_coins(-100);
                player->equip(new Staff());
                cout << "Merchant: 'A stick for a stick figure. Fitting.'\n";
            } else {
                cout << "Merchant: 'You can't afford magic, kid.'\n";
            }
        }
        else {
            cout << "You leave. The merchant counts his money and ignores you.\n";
        }
    }
};


#endif