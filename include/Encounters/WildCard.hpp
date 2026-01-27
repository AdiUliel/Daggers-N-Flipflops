#ifndef WILDCARD_H
#define WILDCARD_H

#include "Encounter.h"
#include "Enemy.h"
#include "Utils.h"
#include <iostream>

using std::cout;
using std::cin;
using std::unique_ptr;

/**
 * @class WildCard
 * @brief Random events that add unpredictability to the run.
 * * Possibilities:
 * 1. Trap (Damage)
 * 2. Shrine (Full Heal)
 * 3. Class Change (The Old Man)
 * 4. Free Loot (Coins)
 */
class WildCard : public Encounter {
public:
    void run(unique_ptr<Character>& player) override {
        int roll = random_int(1, 4);

        if (roll == 1) { // Take Some Damage
            cout << "Walking is hard, isn't it? You tripped over your own feet.\n";
            cout << "It's a Trap! You fell on your knee and scraped it. (Damage taken)\n";
            
            player->damage(player->get_HP() * 0.2);
            cout << "New HP: " << player->get_HP() << "/" << player->get_maxHP() << "\n";
            
        } else if (roll == 2) { // Full Heal
            cout << "A glowing ancient shrine. You touched it? Gross. Who knows where that's been.\n";
            cout << "OH GOD WHY IS IT STICKY??\n";
            player->heal(100000);
            player->set_MP(100000);
            cout << "HP and MP fully restored!\n";

        } else if (roll == 3) { // The Boomer Incident [class change]
            cout << "A sketchy boomer emerges from the shadows. He smells like cabbage.\n";
            cout << "He will sell you 'Destiny Changing Elixir' for 500 coins.\n";
            cout << "Current balance: " << player->get_coins() << "\n";
            string choice = get_string("Buy the suspicious fluids? (y/n): ");
            
            if (choice == "y" || choice == "Y") {
                if (player->get_coins() >= 500) {
                    player->new_coins(-500);
                    cout << "You drank the elixir. It tastes like regret and wet socks.\n";
                    cout << "Immediately you feel like you gotta go to the toilet... SOMETHING is happening.\n";
                    change_player_class(player);
                } else {
                    cout << "Insufficient funds. In other words - Your'e broke son!\n";
                    cout << "The crazy old man pulls out a live baby kangaroo out of his pants, and starts eating it as he walks away.\n";
                    cout << "It screams for its life.\n";
                }
            } else {
                cout << "It's probably for the best. It was likely just vodka-XL mixed with soap.\n";
            } 

        } else { // Find Some Money
            cout << "Oh look. Money on the floor.\n";
            cout << "Pick it up! You need it for your mental health medication.\n";
            int foundCoins = 50 + random_int(-10, 10);
            player->new_coins(foundCoins);
            cout << "You found " << foundCoins << " coins. Do NOT spend it all on avocado toast.\n";
            cout << "Your balance: " << player->get_coins() << " coins.\n";
        }
        cout << "\n--- Encounter finished ---\n";
    }
};

#endif