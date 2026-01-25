#ifndef WILDCARD_H
#define WILDCARD_H

#include "Encounter.h"
#include "Enemy.h"
#include "Utils.h"
#include <iostream>

using std::cout;
using std::cin;
using std::unique_ptr;

class WildCard : public Encounter {
public:
    void run(unique_ptr<Character>& player) override {
        cout << "You stumble upon something...\n";
        int roll = random_int(1, 4);
        if (roll == 1) {
            cout << "It's a Trap! You fell on your knee and scraped it. (Damage taken)\n";
            player->damage(player->get_HP() * 0.2);
            cout << "New HP : " << player->get_HP() << "\n";
            
        } else if (roll == 2) {
            cout << "An ancient shrine! You tried touching it and got this... TINGLE...\n";
            player->heal(100000);
            player->set_MP(100000);
            cout << "HP and MP fully restored!\n";
        } else if (roll == 3) {
            cout << "An old man appears, he looks wise but not trustworthy.\n";
            cout << "He will sell you 'Destiny Changing Elixir' for 500 coins.\n";
            string choice = get_string("Do you want to buy it? (y/n): ");
            if (choice == "y" || choice == "Y") {
                if (player->get_coins() >= 500) {
                    player->new_coins(-500);
                    cout << "You drank the elixir. You feel... different.\n";
                    change_player_class(player);
                } else {
                    cout << "You don't have enough coins. The old man vanishes. Creepy stuff.\n";
                }
            } 
        } else {
            cout << "WOW WOW WOW!\n";
            cout << "You found a hidden stash of coins! Its arround 50 or so.\n";
            player->new_coins(50 + random_int(-10, 10));
            cout << "Your balance: " << player->get_coins() << " coins.\n";
        }
    }
};

#endif